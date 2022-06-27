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

#ifndef BUILD_DEFS_H

#define BUILD_DEFS_H


// Example of __DATE__ string: "Jul 27 2012"
// Example of __TIME__ string: "21:06:19"

#define COMPUTE_BUILD_YEAR \
    ( \
        (__DATE__[ 7] - '0') * 1000 + \
        (__DATE__[ 8] - '0') *  100 + \
        (__DATE__[ 9] - '0') *   10 + \
        (__DATE__[10] - '0') \
    )


#define COMPUTE_BUILD_DAY \
    ( \
        ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') * 10 : 0) + \
        (__DATE__[5] - '0') \
    )


#define BUILD_MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MONTH_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MONTH_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MONTH_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MONTH_IS_DEC (__DATE__[0] == 'D')


#define COMPUTE_BUILD_MONTH \
    ( \
        (BUILD_MONTH_IS_JAN) ?  1 : \
        (BUILD_MONTH_IS_FEB) ?  2 : \
        (BUILD_MONTH_IS_MAR) ?  3 : \
        (BUILD_MONTH_IS_APR) ?  4 : \
        (BUILD_MONTH_IS_MAY) ?  5 : \
        (BUILD_MONTH_IS_JUN) ?  6 : \
        (BUILD_MONTH_IS_JUL) ?  7 : \
        (BUILD_MONTH_IS_AUG) ?  8 : \
        (BUILD_MONTH_IS_SEP) ?  9 : \
        (BUILD_MONTH_IS_OCT) ? 10 : \
        (BUILD_MONTH_IS_NOV) ? 11 : \
        (BUILD_MONTH_IS_DEC) ? 12 : \
        /* error default */  99 \
    )

#define COMPUTE_BUILD_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define COMPUTE_BUILD_MIN  ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define COMPUTE_BUILD_SEC  ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')


#define BUILD_DATE_IS_BAD (__DATE__[0] == '?')

#define BUILD_YEAR  ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_YEAR)
#define BUILD_MONTH ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_MONTH)
#define BUILD_DAY   ((BUILD_DATE_IS_BAD) ? 99 : COMPUTE_BUILD_DAY)

#define BUILD_TIME_IS_BAD (__TIME__[0] == '?')

#define BUILD_HOUR  ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_HOUR)
#define BUILD_MIN   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_MIN)
#define BUILD_SEC   ((BUILD_TIME_IS_BAD) ? 99 :  COMPUTE_BUILD_SEC)


#endif // BUILD_DEFS_H


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
	TTGOClass::getWatch()->rtc->setDateTime(BUILD_YEAR, BUILD_MONTH, BUILD_DAY, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
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
