#include "config.h"
#include "ChargingMode.h"

#include <LilyGoWatch.h>

#include "CyberWatch.h"
#include "Core/Hardware/Esp32.h"
#include "Core/Hardware/MotorController.h"
#include "Core/Hardware/BatteryManager.h"


void ChargingMode::switchedTo() {
	TTGOClass::getWatch()->tft->drawRect(
		26,
		ChargingMode::POS_Y - 4,
		TTGOClass::getWatch()->tft->width() - 60,
		ChargingMode::HEIGHT + 8,
		COLOR_MAIN_1
	);
	TTGOClass::getWatch()->tft->fillRect(
		TTGOClass::getWatch()->tft->width() - 30,
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
	uint8_t widthStep = (TTGOClass::getWatch()->tft->width() - 72) / (100 / step);
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
			TTGOClass::getWatch()->tft->width() - (xStart + 72),
			ChargingMode::HEIGHT - 2,
			COLOR_BACKGROUND
		);
		delay(200);
	}
	this->loops++;
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