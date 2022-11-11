#include "config.h"

#include "KnightRiderBatteryBar.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/BatteryManager.h"
#include "Core/Hardware/Display.h"

void KnightRiderBatteryBar::render() {
	uint8_t capacity = BatteryManager::getInstance()->getCapacity();
	if (
		this->prevCapacity != capacity
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->setTextFont(1);
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->drawString("BATTERY", 17, POS_Y);
		this->renderBar(capacity);
		this->renderBar(100);
		this->prevCapacity = capacity;
		Display::getInstance()->resetTypographySettings();
	}
	this->setShouldReRender(false);
}


void KnightRiderBatteryBar::renderBar(uint8_t capacity) {
	uint8_t barWidth = (TTGOClass::getWatch()->tft->width() - 30);
	TTGOClass::getWatch()->tft->fillRect(
		15,
		POS_Y + 20,
		(barWidth * BATTERY_VERY_LOW) / 100,
		HEIGHT,
		TFT_RED
	);

	TTGOClass::getWatch()->tft->fillRect(
		15 + (barWidth * BATTERY_VERY_LOW) / 100,
		POS_Y + 20,
		(barWidth * (BATTERY_LOW - BATTERY_VERY_LOW)) / 100,
		HEIGHT,
		TFT_YELLOW
	);


	TTGOClass::getWatch()->tft->fillRect(
		15 + (barWidth * BATTERY_LOW) / 100,
		POS_Y + 20,
		15 + barWidth * ((float)(100 - BATTERY_LOW) / 100),
		HEIGHT,
		TFT_GREEN
	);

	for (uint8_t i = 1; i <= 9; i++) {
		TTGOClass::getWatch()->tft->fillRect(
			15 + (barWidth  / 10) * i,
			POS_Y + 20,
			5,
			HEIGHT,
			TFT_BLACK
		);
	}

	TTGOClass::getWatch()->tft->fillRect(
		20 + (barWidth / 100)  * capacity,
		POS_Y + 20,
		(barWidth / 100)  * (100 - capacity) + 30,
		HEIGHT,
		TFT_BLACK
	);


}