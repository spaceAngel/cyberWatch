#include "config.h"

#include <LilyGoWatch.h>

#include "Battery.h"
#include "Core/Hardware/BatteryManager.h"

#include "UserInterface/Icons/Charging.h"
#include "UserInterface/UserInterfaceManager.h"

void Battery::render() {
	uint8_t capacity = BatteryManager::getInstance()->getCapacity();
	if (
		(this->shouldReRender())
		|| (capacity < this->prevCapacity) //avoid blinking cause percentage is oscilating e.g. 94 - 96
		|| (
			(capacity != this->prevCapacity)
			&& (BatteryManager::getInstance()->isCharging() == true)
		)
	) {
		if (this->showCapacity == true) {
			this->renderCapacity(capacity);
		}

		this->renderBatteryIcon(capacity);
		this->prevCapacity = capacity;
	}
	this->setShouldReRender(false);
}

void Battery::renderCapacity(uint8_t capacity) {
	char battery[6];
	(void)snprintf(battery, sizeof(battery), "%d%%", capacity);
	TTGOClass::getWatch()->tft->fillRect(this->posX + 45, this->posY, 70, 26, COLOR_BACKGROUND);
	TTGOClass::getWatch()->tft->setTextColor(
		(capacity <= BATTERY_VERY_LOW) ? COLOR_WARN : COLOR_MAIN_1
	);
	TTGOClass::getWatch()->tft->drawString(battery, this->posX + 48, this->posY + 3);
	TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
}

void Battery::renderBatteryIcon(uint8_t capacity) {
	uint y = this->posY + 5;
	uint x = this->posX + 3;
	uint thick = 2;
	uint height = 17;
	uint width = 32;
	uint innerWidth = (width - 6) - (2 * thick);
	TTGOClass::getWatch()->tft->fillRect(this->posX, this->posY, 45, 26, COLOR_BACKGROUND);
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
