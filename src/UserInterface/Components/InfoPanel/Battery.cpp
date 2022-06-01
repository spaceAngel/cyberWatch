#include "config.h"

#include <LilyGoWatch.h>

#include "Battery.h"
#include "System/BatteryManager.h"

void Battery::render() {
	uint8_t capacity = BatteryManager::getInstance()->getCapacity();
	if (
		(capacity < this->prevCapacity) //avoid blinking cause percentage is oscilating e.g. 94 - 96
		|| (
			(capacity != this->prevCapacity)
			&& (BatteryManager::getInstance()->isCharging() == true)
		)
	) {
		char battery[6];
		(void)snprintf(battery, sizeof(battery), "%d%%", capacity);
		TTGOClass::getWatch()->tft->fillRect(POS_X, POS_Y, 115, 26, COLOR_BACKGROUND);
		TTGOClass::getWatch()->tft->setTextColor(
			(capacity <= BATTERY_VERY_LOW) ? COLOR_WARN : COLOR_MAIN_1
		);
		TTGOClass::getWatch()->tft->drawString(battery, POS_X + 51, POS_Y + 3);
		this->renderBatteryIcon(capacity);
		this->prevCapacity = capacity;
		TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
	}

	if (BatteryManager::getInstance()->isCharging() != this->prevChargingState) {
		if (BatteryManager::getInstance()->isCharging() == true) {
			this->renderChargingIcon();
		} else {
			TTGOClass::getWatch()->tft->fillRect(128, POS_Y + 3, 36, 20, COLOR_BACKGROUND);
		}
		this->prevChargingState = BatteryManager::getInstance()->isCharging();
	}
}

void Battery::renderBatteryIcon(uint8_t capacity) {
	uint y = POS_Y + 4;
	uint x = POS_X + 3;
	uint thick = 2;
	uint height = 18;
	uint width = 36;
	uint innerWidth = (width - 6) - (2 * thick);

	TTGOClass::getWatch()->tft->fillRect(x, y, width, height, (capacity <= BATTERY_VERY_LOW) ? COLOR_WARN : COLOR_MAIN_1);
	TTGOClass::getWatch()->tft->fillRect(
		x + thick,
		y + thick,
		width - (2 * thick),
		height - (2 * thick),
		COLOR_BACKGROUND
	); // inner box

	TTGOClass::getWatch()->tft->fillRect(
		(x + width) - 1,
		y + 4,
		6,
		height - 8,
		(capacity <= BATTERY_VERY_LOW) ? COLOR_WARN : COLOR_MAIN_1
	);

	float percentageBarWidth = ((float)capacity / (float)100) * (float)innerWidth ;
	TTGOClass::getWatch()->tft->fillRect(
		x + thick + 3,
		y + thick + 2,
		(int) percentageBarWidth,
		(height - 4) - (thick * 2),
		(capacity <= BATTERY_LOW) ? COLOR_WARN : COLOR_MAIN_1
	);
}

	void Battery::renderChargingIcon() {
		int posX = 146;
		int posY = POS_Y + 12;
		TTGOClass::getWatch()->tft->fillCircle(posX + 4, posY, 8, COLOR_MAIN_1);
		TTGOClass::getWatch()->tft->fillRect(posX - 15, posY - 2, 11, 4, COLOR_MAIN_1);
		TTGOClass::getWatch()->tft->fillRect(posX + 8, posY - 6, 4, 16, COLOR_BACKGROUND);
		TTGOClass::getWatch()->tft->fillRect(posX + 7, posY - 5, 9, 2, COLOR_MAIN_1);
		TTGOClass::getWatch()->tft->fillRect(posX + 7, posY + 3, 9, 2, COLOR_MAIN_1);
	}
