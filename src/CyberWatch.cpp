#include "config.h"

#include <LilyGoWatch.h>

#include "CyberWatch.h"

#include "System/Display.h"
#include "System/InactivityWatcher.h"
#include "System/Esp32.h"
#include "System/BatteryManager.h"
#include "System/MoveSensor.h"
#include "System/MotorController.h"
#include "UserInterface/UserInterfaceManager.h"

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
	TTGOClass::getWatch()->motor_begin();
	Display::getInstance()->init();
	BatteryManager::getInstance()->energyConsumptionSavingsSettings();
	Esp32::getInstance()->initIRQ();
	MoveSensor::getInstance()->initIRQ();
	UserInterfaceManager::getInstance()->showSplashScreen();
};

void CyberWatch::loop() {
	while(1) {
		bool PEKshort = false;

		this->handleBatteryLowActions();
		this->handleEsp32IRQ(PEKshort);
		if(UserInterfaceManager::getInstance()->isSleepForbidden() == true) {
			InactivityWatcher::getInstance()->markActivity();
		}
		if (
			InactivityWatcher::getInstance()->isInactive()
			&& MoveSensor::getInstance()->isTilt()
		) {
			InactivityWatcher::getInstance()->markActivity();
		}
		if (
			UserInterfaceManager::getInstance()->handleTouch()
			|| PEKshort
		) {
			if (
				!InactivityWatcher::getInstance()->isInactive()
				&& PEKshort
			) {
				UserInterfaceManager::getInstance()->handlePEKShort();
			}
			InactivityWatcher::getInstance()->markActivity();
		}
		if (
			InactivityWatcher::getInstance()->isInactive() == true
		) {
			Display::getInstance()->turnDisplayOff();
			esp_sleep_enable_timer_wakeup(TICK_SLEEP);
			esp_sleep_enable_ext1_wakeup(GPIO_SEL_39, ESP_EXT1_WAKEUP_ANY_HIGH);
			esp_light_sleep_start();
		} else {
		if (!Display::getInstance()->isDisplayOn()) {
			Display::getInstance()->turnDisplayOn();
		}
		UserInterfaceManager::getInstance()->render();
		delay(TICK_WAKEUP);
		}
	}
};

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
