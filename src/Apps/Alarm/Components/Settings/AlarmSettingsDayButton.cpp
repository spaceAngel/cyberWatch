#include "config.h"

#include "AlarmSettingsDayButton.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"
#include "Apps/Alarm/AlarmStorage.h"
#include "Core/Hardware/MotorController.h"

void AlarmSettingsDayButton::render() {

	const char * days[7] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

	TTGOClass::getWatch()->tft->drawRect(
		this->getPosX(),
		this->getPosY(),
		this->getWidth(),
		AlarmSettingsDayButton::HEIGHT,
		COLOR_MAIN_1
	);
	TTGOClass::getWatch()->tft->setTextColor(
		AlarmStorage::getInstance()->getAlarm(this->alarm)->getIsEnabledForDay(this->day) ? COLOR_MAIN_1  : COLOR_MAIN_3
	);
	TTGOClass::getWatch()->tft->drawString(
		days[this->day],
		this->getPosX() + (this->getWidth() - TTGOClass::getWatch()->tft->textWidth(days[this->day])) / 2,
		this->getPosY() + (AlarmSettingsDayButton::HEIGHT - TTGOClass::getWatch()->tft->fontHeight()) / 2 + 2
	);

	Display::getInstance()->resetTypographySettings();
}

uint8_t AlarmSettingsDayButton::getWidth() {
	return TFT_WIDTH / 5;
}


uint8_t AlarmSettingsDayButton::getPosX() {
	return (TFT_WIDTH - (this->day >= 4 ? 3 : 4) * (this->getWidth() + 10) ) / 2
	+ ((this->day % 4) * (this->getWidth() + 10));
}

uint8_t AlarmSettingsDayButton::getPosY() {
	return AlarmSettingsDayButton::POS_Y + (this->day >= 4 ? AlarmSettingsDayButton::HEIGHT + 6 : 0);
}

