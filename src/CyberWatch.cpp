#include "config.h"

#include <LilyGoWatch.h>
#include <SPIFFS.h>

#include "CyberWatch.h"

#include "Core/Hardware/Display.h"
#include "Core/InactivityWatcher.h"
#include "Core/SystemTicker.h"
#include "Core/Hardware/Esp32.h"
#include "Core/Hardware/BatteryManager.h"
#include "Core/Hardware/MoveSensor.h"
#include "Core/Hardware/MotorController.h"
#include "UserInterface/UserInterfaceManager.h"
#include "Environment/RunAfterCompilation.h"
#include "Environment/AppSettings.h"
#include "Environment/SystemInfo.h"
#include "Core/SystemTicker.h"

#include "Events/EventManager.h"

CyberWatch* CyberWatch::inst;

CyberWatch *CyberWatch::getInstance() {
	if (CyberWatch::inst == nullptr) {
CyberWatch::inst = new CyberWatch();
	}
	return CyberWatch::inst;
}

void CyberWatch::init() {

	Serial.begin(SERIAL_RATE);
	Serial.println("cyberWatch starting");

	TTGOClass::getWatch()->begin();

	#ifdef LILYGO_WATCH_HAS_MOTOR
		TTGOClass::getWatch()->motor_begin();
	#endif

	SPIFFS.begin();
	RunAfterCompilation::handle();
	Display::getInstance()->init();
	BatteryManager::getInstance()->energyConsumptionSavingsSettings();
	Esp32::getInstance()->initIRQ();
	MoveSensor::getInstance()->initIRQ();
	UserInterfaceManager::getInstance()->showSplashScreen();
	SystemTicker::getInstance();
	SystemInfo::getInstance();
};

void CyberWatch::loop() {
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

void CyberWatch::executeLoopActions() {
	BatteryManager::getInstance()->updateCapacity();
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

void CyberWatch::executeLoopSleep() {
	this->sleep();
	SystemTicker::getInstance()->tickSleep();
}

void CyberWatch::executeLoopWakeUp() {
	//if display is "always on" but not forbidden by any component, go to default screen and lock screen after inactivity interval
	if (
		(UserInterfaceManager::getInstance()->isSleepForbidden() == false)
		&& (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) == true)
		&& (InactivityWatcher::getInstance()->isInactive() == true)
	) {
		UserInterfaceManager::getInstance()->setToDefaultApp();
		UserInterfaceManager::getInstance()->setIsLocked(true);
	}
	//SystemTicker::getInstance()->tickWakedUp();
	this->handleWakeupTick();
}

void CyberWatch::checkIfTiltIrqAndMarkAsActive() {
	if (
		InactivityWatcher::getInstance()->isInactive()
		&& AppSettings::getInstance()->get(APPSETTINGS_TILT_ON) == true
		&& MoveSensor::getInstance()->isTilt() == true
	) {
		InactivityWatcher::getInstance()->markActivity();
	}
}

bool CyberWatch::isSleepForbidden() {
	return (UserInterfaceManager::getInstance()->isSleepForbidden() == true)
	|| (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) == true);
}

void CyberWatch::handleWakeupTick() {
	if (!Display::getInstance()->isDisplayOn()) {
		Display::getInstance()->turnDisplayOn();
		UserInterfaceManager::getInstance()->setToDefaultApp();
		UserInterfaceManager::getInstance()->setIsLocked(true);
	}
	UserInterfaceManager::getInstance()->render();
	delay(TICK_WAKEUP);
}

void CyberWatch::sleep() {
	Display::getInstance()->turnDisplayOff();
	esp_sleep_enable_timer_wakeup(SLEEPCYCLE_MS * 1000);
	esp_light_sleep_start();
}

void CyberWatch::turnOff() {
	Display::getInstance()->turnDisplayOn();
	UserInterfaceManager::getInstance()->showExitScreen();
	MotorController::vibrate(2);
	delay(2000);
	TTGOClass::getWatch()->shutdown();
}

void CyberWatch::handleCabelConnection() {
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

void CyberWatch::handleEsp32IRQ(bool &PEKshort) {
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

CyberWatch::CyberWatch() {
}
