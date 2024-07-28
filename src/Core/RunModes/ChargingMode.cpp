#include "config.h"
#include "ChargingMode.h"

#include <LilyGoWatch.h>

#include "CyberWatch.h"
#include "Core/Hardware/Esp32.h"
#include "Core/Hardware/BatteryManager.h"
#include "Core/Hardware/RTC.h"
#include "Core/Hardware/Display.h"
#include "Core/Hardware/MotorController.h"
#include "Utils/DateUtil.h"


void ChargingMode::switchedTo() {
	delay(100);
	TTGOClass::getWatch()->tft->fillScreen(
		COLOR_BACKGROUND
	);
	TTGOClass::getWatch()->tft->drawRect(
		26,
		ChargingMode::POS_Y - 4,
		RESOLUTION_WIDTH - 60,
		ChargingMode::HEIGHT + 8,
		COLOR_MAIN_1
	);
	TTGOClass::getWatch()->tft->fillRect(
		RESOLUTION_WIDTH - 30,
		POS_Y + (HEIGHT * 0.25),
		6,
		HEIGHT * 0.5,
		COLOR_MAIN_1
	);
	this->loops = 100;
}

void ChargingMode::loop() {
	this->handleEsp32IRQ();

	uint8_t batteryCharge = BatteryManager::getInstance()->getUpdatedCapacity();
	uint8_t step = 10;
	uint8_t widthStep = (RESOLUTION_WIDTH - 72) / (100 / step);
	uint8_t xStart = widthStep * (((batteryCharge - (+ batteryCharge % step))) / step);

	if (this->loops % step == 0 && batteryCharge != 100)  {
		TTGOClass::getWatch()->tft->fillRect(
			4 + 31 + xStart + (((this->loops - batteryCharge) / step ))  * widthStep,
			1 + ChargingMode::POS_Y,
			widthStep - 5,
			ChargingMode::HEIGHT - 2,
			COLOR_MAIN_1
		);
	}

	delay(100);
	if  (this->loops == 100) {
		this->loops = batteryCharge - (batteryCharge % step);
		TTGOClass::getWatch()->tft->fillRect(
			31,
			1 + ChargingMode::POS_Y,
			xStart + 1,
			ChargingMode::HEIGHT - 2,
			COLOR_MAIN_1
		);

		TTGOClass::getWatch()->tft->fillRect(
			31 + xStart,
			1 + ChargingMode::POS_Y,
			RESOLUTION_WIDTH - (xStart + 72),
			ChargingMode::HEIGHT - 2,
			COLOR_BACKGROUND
		);
		delay(200);
	}
	this->renderDateTime();
	this->loops++;
}

void ChargingMode::renderDateTime() {

	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (currentTime.minute != this->prevMinute) {
		Display::getInstance()->resetTypographySettings();
		this->prevMinute = currentTime.minute;
		TTGOClass::getWatch()->tft->fillRect(
			0,
			ChargingMode::POS_Y + 55,
			RESOLUTION_WIDTH,
			135,
			COLOR_BACKGROUND
		);

		char dayInWeek[10];
		DateUtil::weekdayName(dayInWeek, currentTime.year, currentTime.month, currentTime.day);
		TTGOClass::getWatch()->tft->drawString(
			dayInWeek,
			25,
			ChargingMode::POS_Y + 155
		);

		char dateStr[11];
		(void)snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", currentTime.day, currentTime.month, currentTime.year);
		TTGOClass::getWatch()->tft->setTextSize(1);
		TTGOClass::getWatch()->tft->drawString(
			dateStr,
			25,
			ChargingMode::POS_Y + 130
		);

		char timeStr[6];
		(void)snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);
		TTGOClass::getWatch()->tft->setTextSize(3);
		TTGOClass::getWatch()->tft->drawString(
			timeStr,
			15,
			ChargingMode::POS_Y + 60
		);

	}
}

void ChargingMode::handleEsp32IRQ() {
	if (Esp32::getInstance()->isIRQ() == true) {
		TTGOClass::getWatch()->power->readIRQ();
		if (TTGOClass::getWatch()->power->isPEKLongtPressIRQ() == true) {
			CyberWatch::getInstance()->setRunMode(RUNMODE_MAIN);
		}
		this->handleCabelConnection();
		Esp32::getInstance()->cleanIRQ();
	}
}

void ChargingMode::handleCabelConnection() {
	if (
		BatteryManager::getInstance()->handleCabelPlugRemoveIRQ() == true
	) {
		TTGOClass::getWatch()->shutdown();
	}
}