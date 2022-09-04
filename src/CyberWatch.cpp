#include "config.h"

#include <LilyGoWatch.h>
#include <SPIFFS.h>

#include "CyberWatch.h"

#include "System/Display.h"
#include "System/InactivityWatcher.h"
#include "System/Esp32.h"
#include "System/BatteryManager.h"
#include "System/MoveSensor.h"
#include "System/MotorController.h"
#include "UserInterface/UserInterfaceManager.h"
#include "Environment/RunAfterCompilation.h"
#include "Environment/AppSettings.h"

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
	this->handleBatteryLowActions();
	this->handleEsp32IRQ(PEKshort);
	if(
		UserInterfaceManager::getInstance()->isSleepForbidden() == true
		|| AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON)
	) {
		InactivityWatcher::getInstance()->markActivity();
	}
	if (
		InactivityWatcher::getInstance()->isInactive()
		&& MoveSensor::getInstance()->isTilt()
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
	} else {
		this->handleWakeupTick();
	}
};

void CyberWatch::handleWakeupTick() {
	if (!Display::getInstance()->isDisplayOn()) {
		Display::getInstance()->turnDisplayOn();
	}
	UserInterfaceManager::getInstance()->render();
	delay(TICK_WAKEUP);
}

void CyberWatch::sleep() {
	Display::getInstance()->turnDisplayOff();
	esp_sleep_enable_timer_wakeup(TICK_SLEEP);
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
		if (capacity == BATTERY_LOW) {
			vibrationCount = 1;
		}

		if (capacity == BATTERY_VERY_LOW) {
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
