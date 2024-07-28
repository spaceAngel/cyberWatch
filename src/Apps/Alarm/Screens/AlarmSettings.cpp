#include "config.h"

#include "AlarmSettings.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"
#include "Apps/Alarm/Components/Settings/AlarmSettingsDayButton.h"
#include "Apps/Alarm/AlarmModel.h"
#include "Apps/Alarm/AlarmStorage.h"
#include "UserInterface/AppRunner.h"
#include "Core/Hardware/MotorController.h"
#include "Core/Hardware/RTC.h"

void AlarmSettings::render() {
	if (this->shouldReRender()) {
		TTGOClass::getWatch()->tft->drawString(
			"Alarm settings",
			(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth("Alarm settings")) / 2,
			25
		);
		Display::getInstance()->resetTypographySettings();
		this->renderButtons();
		this->setShouldReRender(false);
	}

	for (uint8_t i; i<7; i++) {
		this->dayButtons[i]->render();
	}

	this->spinnerHour->render();
	this->spinnerMinute->render();

}

void AlarmSettings::renderButtons() {
	uint8_t btnLeft = RESOLUTION_WIDTH - AlarmSettings::BTN_WIDTH - 10;
	TTGOClass::getWatch()->tft->drawRect(
		btnLeft,
		60,
		AlarmSettings::BTN_WIDTH,
		AlarmSettings::BTN_HEIGHT,
		COLOR_MAIN_1
	);

	TTGOClass::getWatch()->tft->fillRect(
		btnLeft + 1,
		61,
		AlarmSettings::BTN_WIDTH - 2,
		AlarmSettings::BTN_HEIGHT - 2,
		AlarmStorage::getInstance()->getAlarm(this->alarm)->isRunningOnce() ? COLOR_MAIN_1 : COLOR_BACKGROUND
	);

	TTGOClass::getWatch()->tft->setTextColor(
		AlarmStorage::getInstance()->getAlarm(this->alarm)->isRunningOnce() ? COLOR_BACKGROUND : COLOR_MAIN_1
	);
	TTGOClass::getWatch()->tft->drawString(
		"Once",
		btnLeft + (AlarmSettings::BTN_WIDTH - TTGOClass::getWatch()->tft->textWidth("Once"))/ 2,
		60 + (AlarmSettings::BTN_HEIGHT - TTGOClass::getWatch()->tft->fontHeight()) / 2 + 2
	);

	TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
	TTGOClass::getWatch()->tft->drawRect(
		btnLeft,
		112,
		AlarmSettings::BTN_WIDTH,
		AlarmSettings::BTN_HEIGHT,
		TFT_RED
	);
	TTGOClass::getWatch()->tft->drawString(
		"Delete",
		btnLeft + (AlarmSettings::BTN_WIDTH - TTGOClass::getWatch()->tft->textWidth("Delete"))/ 2,
		112 + (AlarmSettings::BTN_HEIGHT - TTGOClass::getWatch()->tft->fontHeight()) / 2 + 2
	);
}

bool AlarmSettings::handleTouch(uint8_t x, uint8_t y) {
	if (
		x > 10 && x < 60
		&& y > AlarmSettingsTimeSpinner::POS_Y && y < AlarmSettingsTimeSpinner::POS_Y + 100
	) {
		this->spinnerHour->handleTouch(x, y);
	}

	if (
		x > 70 && x < 130
		&& y > AlarmSettingsTimeSpinner::POS_Y && y < AlarmSettingsTimeSpinner::POS_Y + 100
	) {
		this->spinnerMinute->handleTouch(x, y);
	}
	if (
		y > AlarmSettingsDayButton::POS_Y
		&& y < AlarmSettingsDayButton::POS_Y + 10 + 2 * AlarmSettingsDayButton::HEIGHT
	) {
		for (uint8_t i; i<7; i++) {
			if (
				x > this->dayButtons[i]->getPosX() && x < this->dayButtons[i]->getPosX() + this->dayButtons[i]->getWidth()
				&& y > this->dayButtons[i]->getPosY() && y < this->dayButtons[i]->getPosY() + AlarmSettingsDayButton::HEIGHT
			) {
				AlarmStorage::getInstance()->getAlarm(this->alarm)->setIsEnabledForDay(
					i,
					!AlarmStorage::getInstance()->getAlarm(this->alarm)->getIsEnabledForDay(i)
				);
			}
			this->setShouldReRender(true);
		}
	}
	uint8_t btnLeft = RESOLUTION_WIDTH - AlarmSettings::BTN_WIDTH - 10;
	if (x > btnLeft && x < btnLeft + AlarmSettings::BTN_WIDTH) {
		if (y > 60 && y < 60 + AlarmSettings::BTN_HEIGHT) {
			AlarmStorage::getInstance()->getAlarm(this->alarm)->setIsRunningOnce();
			this->setShouldReRender(true);
		}

		if (y > 112 && y < 112 + AlarmSettings::BTN_HEIGHT) {
			AlarmStorage::getInstance()->getAlarm(this->alarm)->setEnabled(false);
			AlarmStorage::getInstance()->save();
			AppRunner::getInstance()->removeAppOnTop();
		}
	}
	AlarmStorage::getInstance()->save();
	return false;
}

bool AlarmSettings::handlePEKShort() {
	AppRunner::getInstance()->removeAppOnTop();
	return false;
}

AlarmSettings::AlarmSettings(uint8_t alarm) {
	this->spinnerHour = new AlarmSettingsTimeSpinner(
		10,
		23,
		[alarm]() {return  AlarmStorage::getInstance()->getAlarm(alarm)->getHour();},
		[alarm](uint8_t value) {return  AlarmStorage::getInstance()->getAlarm(alarm)->setHour(value);}
	);
	this->spinnerMinute = new AlarmSettingsTimeSpinner(
		75,
		59,
		[alarm]() {return  AlarmStorage::getInstance()->getAlarm(alarm)->getMinute();},
		[alarm](uint8_t value) {return  AlarmStorage::getInstance()->getAlarm(alarm)->setMinute(value);}
	);

	for (uint8_t i;+ i<7; i++) {
		this->dayButtons[i] = new AlarmSettingsDayButton(alarm, i);
	}
	this->alarm = alarm;
	if (AlarmStorage::getInstance()->getAlarm(this->alarm)->getEnabled() == false) {
		RTC_Date time = RTC::getInstance()->getCurrentDate();
		AlarmStorage::getInstance()->getAlarm(this->alarm)->setEnabled(true);
		AlarmStorage::getInstance()->getAlarm(this->alarm)->setHour(time.hour < 23 ? time.hour + 1 : 0);
		AlarmStorage::getInstance()->getAlarm(this->alarm)->setMinute(time.minute);
	}
}
