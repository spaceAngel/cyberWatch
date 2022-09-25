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
#include "Core/SystemTicker.h"

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
};

void CyberWatch::loop() {
	bool PEKshort = false;
	if (SystemTicker::getInstance()->isTickFor(TICKER_BATTERY)) {
		this->handleBatteryLowActions();
	}
	this->handleEsp32IRQ(PEKshort);
	if(
		(UserInterfaceManager::getInstance()->isSleepForbidden() == true)
		|| (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) == true)
	) {
		InactivityWatcher::getInstance()->markActivity();
	}
	if (
		InactivityWatcher::getInstance()->isInactive()
		&& AppSettings::getInstance()->get(APPSETTINGS_TILT_ON) == true
		&& MoveSensor::getInstance()->isTilt() == true
	) {
		InactivityWatcher::getInstance()->markActivity();
	}
	if (
		UserInterfaceManager::getInstance()->handleTouch() || PEKshort
	) {
		if (
			!InactivityWatcher::getInstance()->isInactive() && PEKshort
		) {
			UserInterfaceManager::getInstance()->handlePEKShort();
		}
		InactivityWatcher::getInstance()->markActivity();
	}
	if (
		InactivityWatcher::getInstance()->isInactive() == true
	) {
		this->sleep();
		SystemTicker::getInstance()->tickSleep();
	} else {
		SystemTicker::getInstance()->tickWakedUp();
		this->handleWakeupTick();
	}
};

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
	if (BatteryManager::getInstance()->handleCabelPlugInIRQ() == true) {
		MotorController::vibrate(1);
	}
	if (
		(BatteryManager::getInstance()->handleCabelPlugInIRQ() == true)
		|| (BatteryManager::getInstance()->handleCabelPlugRemoveIRQ() == true)
	) {
		InactivityWatcher::getInstance()->markActivity();
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


void CyberWatch::handleBatteryLowActions() {
	int32_t vibrationCount = 0;
	uint8_t capacity = BatteryManager::getInstance()->getCapacity();
	if (BatteryManager::getInstance()->isCharging() == true) {
		this->batteryLowWarnVibrateOnLevel = 101;
	} else {
		if (capacity == (uint8_t)BATTERY_LOW) {
			vibrationCount = 1;
		}

		if (capacity == (uint8_t)BATTERY_VERY_LOW) {
			vibrationCount = 2;
		}

		if (
			(vibrationCount > 0)
			&& (capacity < this->batteryLowWarnVibrateOnLevel)
		) {
			InactivityWatcher::getInstance()->markActivity();
			MotorController::vibrate(vibrationCount);
			this->batteryLowWarnVibrateOnLevel = capacity;
		}
	}
}

CyberWatch::CyberWatch() {
}
