#include "MainMode.h"

#include "CyberWatch.h"
#include "UserInterface/UserInterfaceManager.h"
#include "Core/InactivityWatcher.h"
#include "Core/Hardware/Display.h"
#include "Core/Hardware/Esp32.h"
#include "Core/Hardware/BatteryManager.h"
#include "Core/Hardware/MoveSensor.h"
#include "Core/Hardware/MotorController.h"
#include "Core/Hardware/RTC.h"
#include "Environment/AppSettings.h"
#include "Environment/SystemInfo.h"
#include "Core/SystemTicker.h"
#include "Events/EventManager.h"
#include "UserInterface/Screens/MainScreen.h"
#include "UserInterface/AppRunner.h"
#include "Apps/BlankScreen.h"


void MainMode::switchedTo() {
	MainScreen::getInstance()->destroy();
	UserInterfaceManager::getInstance()->showSplashScreen();
	InactivityWatcher::getInstance()->markActivity();
	AppRunner::getInstance()->setToDefaultApp();
	AppRunner::getInstance()->getCurrentApp()->setShouldReRender(true);
};

void MainMode::loop() {
	bool PEKshort = false;
	this->handleEsp32IRQ(PEKshort);

	this->checkIfTiltIrqAndMarkAsActive();

	if (
		UserInterfaceManager::getInstance()->handleTouch() || PEKshort
	) {
		if (
			(
				!InactivityWatcher::getInstance()->isInactive()
				|| this->isSleepForbidden()
			)
			&& PEKshort
		) {
			UserInterfaceManager::getInstance()->handlePEKShort();
		}
		InactivityWatcher::getInstance()->markActivity();
	}

	this->executeLoopActions();
};

void MainMode::executeLoopActions() {
	BatteryManager::getInstance()->updateCapacity();
	RTC::getInstance()->updateDate();
	InactivityWatcher::getInstance()->checkAndMarkIfOnHand();
	if (
		(InactivityWatcher::getInstance()->isInactive() == false)
		|| (UserInterfaceManager::getInstance()->isSleepForbidden() == true)
		|| (
			AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) == true
			&& InactivityWatcher::getInstance()->isDetectedOnHand()
		)
	) {
		this->executeLoopWakeUp();
	} else {
		this->executeLoopSleep();
	}
}

void MainMode::executeLoopSleep() {
	this->sleep();
	SystemTicker::getInstance()->tickSleep();
}

void MainMode::executeLoopWakeUp() {
	//if display is "always on" but not forbidden by any component, go to default screen and lock screen after inactivity interval
	if (
		(UserInterfaceManager::getInstance()->isSleepForbidden() == false)
		&& (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) == true)
		&& (InactivityWatcher::getInstance()->isInactive() == true)
	) {
		UserInterfaceManager::getInstance()->setToDefaultApp();
		UserInterfaceManager::getInstance()->setIsLocked(true);
	}
	this->handleWakeupTick();
}

void MainMode::checkIfTiltIrqAndMarkAsActive() {
	if (
		InactivityWatcher::getInstance()->isInactive()
		&& AppSettings::getInstance()->get(APPSETTINGS_TILT_ON) == true
		&& MoveSensor::getInstance()->isTilt() == true
	) {
		InactivityWatcher::getInstance()->markActivity();
	}
}

bool MainMode::isSleepForbidden() {
	return (UserInterfaceManager::getInstance()->isSleepForbidden() == true)
	|| (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) == true);
}

void MainMode::handleWakeupTick() {
	if (!Display::getInstance()->isDisplayOn()) {
		Display::getInstance()->turnDisplayOn();
		UserInterfaceManager::getInstance()->setToDefaultApp();
		UserInterfaceManager::getInstance()->setIsLocked(true);
	}
	UserInterfaceManager::getInstance()->render();
	delay(TICK_WAKEUP);
}

void MainMode::sleep() {
	Display::getInstance()->turnDisplayOff();
	esp_sleep_enable_timer_wakeup(SLEEPCYCLE_MS * 1000);
	esp_light_sleep_start();
}

void MainMode::handleCabelConnection() {
	if (
		BatteryManager::getInstance()->handleCabelPlugInIRQ() == true
		|| BatteryManager::getInstance()->handleCabelPlugRemoveIRQ() == true
	) {
		SystemInfo::getInstance()->setPlugState(
			!BatteryManager::getInstance()->handleCabelPlugRemoveIRQ()
		);
		EventManager::getInstance()->fireEvent(EVENT_CABLE_PLUG);
	}
}

void MainMode::handleEsp32IRQ(bool &PEKshort) {
	if (Esp32::getInstance()->isIRQ() == true) {
		TTGOClass::getWatch()->power->readIRQ();
		if (TTGOClass::getWatch()->power->isPEKLongtPressIRQ() == true) {
			this->turnOff();
		}
		this->handleCabelConnection();
		if (TTGOClass::getWatch()->power->isPEKShortPressIRQ() == true) {
			PEKshort = true;
		}
		Esp32::getInstance()->cleanIRQ();
	}
}


void MainMode::turnOff() {
	Display::getInstance()->turnDisplayOn();
	UserInterfaceManager::getInstance()->showExitScreen();
	MotorController::vibrate(2);
	delay(2000);
	if (
		BatteryManager::getInstance()->isCharging()
		|| SystemInfo::getInstance()->getPluggedIn()
	) {
		AppRunner::getInstance()->setAppOnTop(new BlankScreen());
		AppRunner::getInstance()->getCurrentApp()->render();
		CyberWatch::getInstance()->setRunMode(RUNMODE_CHARGING);
	} else {
		TTGOClass::getWatch()->shutdown();
	}
}