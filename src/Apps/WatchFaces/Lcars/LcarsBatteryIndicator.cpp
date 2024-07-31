#include "config.h"
#include "LcarsBatteryIndicator.h"

#include <LilyGoWatch.h>
#include "UserInterface/UserInterfaceManager.h"
#include "Core/Hardware/BatteryManager.h"
#include "Environment/SystemInfo.h"

void LcarsBatteryIndicator::render() {
	uint8_t capacity = BatteryManager::getInstance()->getCapacity();
	if (
		this->shouldReRender()
		|| (capacity < this->prevCapacity) //avoid blinking cause percentage is oscilating e.g. 94 - 96
		|| ((SystemInfo::getInstance()->getPluggedIn() != this->prevCharging)
		||	(capacity != this->prevCapacity)
			&& (SystemInfo::getInstance()->getPluggedIn() == true)
		)
	) {
		TTGOClass::getWatch()->tft->fillRect(42, 196, 190, 20, TFT_BLACK);
		TTGOClass::getWatch()->tft->setTextColor(capacity < 25 ? TFT_RED : TFT_PINK);
		char battery[8];
		(void)snprintf(battery, sizeof(battery), "PW %d%%", capacity);
		TTGOClass::getWatch()->tft->drawString(
			battery,
			52,
			196
		);
		TTGOClass::getWatch()->tft->setTextColor(TFT_PINK);
		this->setShouldReRender(false);
		this->prevCapacity = capacity;
		this->prevCharging = SystemInfo::getInstance()->getPluggedIn();

		TTGOClass::getWatch()->tft->setTextColor(SystemInfo::getInstance()->getPluggedIn() ?  TFT_PINK : TFT_DARKGREY);
		TTGOClass::getWatch()->tft->drawString("CON", 170, 196);
	}
}