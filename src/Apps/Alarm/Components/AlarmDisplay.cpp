#include "config.h"

#include "AlarmDisplay.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"
#include "Apps/Alarm/AlarmStorage.h"

void AlarmDisplay::render() {
	if (this->shouldReRender()) {
		TTGOClass::getWatch()->tft->setTextFont(2);
		uint8_t posY = this->getY();
		TTGOClass::getWatch()->tft->fillRect(
			0,
			posY,
			TTGOClass::getWatch()->tft->width(),
			50,
			COLOR_BACKGROUND
		);
		TTGOClass::getWatch()->tft->setTextSize(3);
		char timeStr[6];
		TTGOClass::getWatch()->tft->setTextColor(
			AlarmStorage::getInstance()->getAlarm(this->line)->getEnabled() ? COLOR_MAIN_1 : COLOR_MAIN_3
		);
		(void)snprintf(
			timeStr,
			sizeof(timeStr),
			"%02d:%02d",
			AlarmStorage::getInstance()->getAlarm(this->line)->getHour(),
			AlarmStorage::getInstance()->getAlarm(this->line)->getMinute()
		);
		TTGOClass::getWatch()->tft->drawString(
			timeStr,
			10,
			posY + 1
		);

		const char * days[7] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

		uint8_t prevX;
		TTGOClass::getWatch()->tft->setTextSize(1);

		for (uint8_t i = 0; i < 7; i++) {
			TTGOClass::getWatch()->tft->setTextColor(
				AlarmStorage::getInstance()->getAlarm(this->line)->getIsEnabledForDay(i) ? COLOR_MAIN_1  : COLOR_MAIN_3
			);
			if (i % 5 == 0) {
				prevX = 130;
			}
			TTGOClass::getWatch()->tft->drawString(
				days[i],
				prevX,
				(i >= 5 ? 25 : 9 ) + posY
			);
			prevX += 4 + TTGOClass::getWatch()->tft->textWidth(days[i]);
		}
		Display::getInstance()->resetTypographySettings();
	}
	this->setShouldReRender(false);
}

uint8_t AlarmDisplay::getY() {
	return 60 + 60 * this->line;
}