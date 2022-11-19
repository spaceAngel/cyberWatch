#include "config.h"

#include "AlarmSettingsTimeSpinner.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"

void AlarmSettingsTimeSpinner::render() {
	if (this->shouldReRender()) {
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->fillRect(
			this->posX,
			AlarmSettingsTimeSpinner::POS_Y,
			AlarmSettingsTimeSpinner::WIDTH,
			AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT * 2 + TTGOClass::getWatch()->tft->fontHeight(),
			COLOR_BACKGROUND
		);
		char valueStr[3];
		(void)snprintf(valueStr, sizeof(valueStr), "%02d", this->getter());
		TTGOClass::getWatch()->tft->drawString(
			valueStr,
			this->posX,
			AlarmSettingsTimeSpinner::POS_Y + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT + 1
		);

		this->renderTriangleButtons();
		Display::getInstance()->resetTypographySettings();
	}
	this->setShouldReRender(false);
}


bool AlarmSettingsTimeSpinner::handleTouch(uint8_t x, uint8_t y) {
	TTGOClass::getWatch()->tft->setTextSize(2); //cause calculating with font height in increase/decrease regions
	if (
		y > AlarmSettingsTimeSpinner::POS_Y
		&& y < AlarmSettingsTimeSpinner::POS_Y + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT + TTGOClass::getWatch()->tft->fontHeight() / 2
	 ) {
		if (this->getter() == 0) {
			this->setter(this->maxValue);
		} else {
			this->setter(this->getter() - 1);
		}

		this->setShouldReRender(true);
	}
	if (
		y > AlarmSettingsTimeSpinner::POS_Y + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT + TTGOClass::getWatch()->tft->fontHeight() / 2
		&& y< AlarmSettingsTimeSpinner::POS_Y  + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT * 2 + TTGOClass::getWatch()->tft->fontHeight() -3
	) {
		if (this->getter() == this->maxValue) {
			this->setter(0);
		} else {
			this->setter(this->getter() + 1);
		}
		this->setShouldReRender(true);
	}
	Display::getInstance()->resetTypographySettings();
	return true;
}

void AlarmSettingsTimeSpinner::renderTriangleButtons() {
		TTGOClass::getWatch()->tft->drawTriangle(
		this->posX + 5,
		AlarmSettingsTimeSpinner::POS_Y + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT,
		this->posX + AlarmSettingsTimeSpinner::WIDTH - 10,
		AlarmSettingsTimeSpinner::POS_Y + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT,
		this->posX + (AlarmSettingsTimeSpinner::WIDTH / 2),
		AlarmSettingsTimeSpinner::POS_Y,
		COLOR_MAIN_1
	);

	TTGOClass::getWatch()->tft->drawTriangle(
		this->posX + 5,
		AlarmSettingsTimeSpinner::POS_Y + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT + TTGOClass::getWatch()->tft->fontHeight() - 3,
		this->posX + AlarmSettingsTimeSpinner::WIDTH - 10,
		AlarmSettingsTimeSpinner::POS_Y + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT + TTGOClass::getWatch()->tft->fontHeight() - 3,
		this->posX + (AlarmSettingsTimeSpinner::WIDTH / 2),
		AlarmSettingsTimeSpinner::POS_Y  + AlarmSettingsTimeSpinner::TRIANGLE_HEIGHT * 2 + TTGOClass::getWatch()->tft->fontHeight() -3,
		COLOR_MAIN_1
	);
}