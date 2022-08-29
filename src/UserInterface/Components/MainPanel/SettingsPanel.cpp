#include "config.h"

#include "SettingsPanel.h"
#include "UserInterface/UserInterfaceManager.h"
#include "UserInterface/Icons/LightBulb.h"
#include "Environment/AppSettings.h"

#include <LilyGoWatch.h>

#include "System/MotorController.h"

SettingsPanel::SettingsPanel() {
	this->lastMask = AppSettings::getInstance()->getSettingsByteMask();
}

void SettingsPanel::render() {
	if (
		this->lastMask != AppSettings::getInstance()->getSettingsByteMask()
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(
			0,
			0,
			TTGOClass::getWatch()->tft->width(),
			150,
			COLOR_BACKGROUND
		);
		this->lastMask = AppSettings::getInstance()->getSettingsByteMask();
		this->setShouldReRender(false);
		this->renderDisplayButton();
		this->renderButton("TILT", 2, 1, true);
		this->renderButton("VIBRATE", 1, 2, true);
		this->renderButton("SOUND", 2, 2, false);
	}
}

void SettingsPanel::renderDisplayButton() {
	this->renderButton("DISPLAY", 1, 1, AppSettings::getInstance()->getAlwaysOn());
}

void SettingsPanel::renderButton(char *btnText, uint8_t col, uint8_t row, boolean isOn) {

	TTGOClass::getWatch()->tft->fillRect(
		5 + (col == 1 ? 0 : (TTGOClass::getWatch()->tft->width() / 2)),
		13 + (row - 1) * 71,
		(TTGOClass::getWatch()->tft->width() / 2) - 10,
		62,
		isOn ? COLOR_MAIN_1 : COLOR_BACKGROUND
	);
	uint8_t posX= (((TTGOClass::getWatch()->tft->width() / 2) - TTGOClass::getWatch()->tft->textWidth(btnText))) / 2;
	if (col == 2) {
		posX = posX + (TTGOClass::getWatch()->tft->width() / 2);
	}
	TTGOClass::getWatch()->tft->setTextColor(isOn ? COLOR_BACKGROUND : COLOR_MAIN_1);
	TTGOClass::getWatch()->tft->drawString(
		btnText,
		posX,
		35+ ((row - 1) * 70)
	);
	TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
}

bool SettingsPanel::handlePEKShort() {
	return false;
}

bool SettingsPanel::controlModeIsTouch() {
	return true;
}

bool SettingsPanel::handleTouch(uint8_t x, uint8_t y) {
	return this->handleDisplayButtonClick(x, y);
}

bool SettingsPanel::handleDisplayButtonClick(uint8_t x, uint8_t y) {
	if (
		x > 5 && x < (TTGOClass::getWatch()->tft->width() / 2) - 10
		&& y > 13 && y < 13 + 71
	) {
		AppSettings::getInstance()->switchAlwaysOn();
		this->renderDisplayButton();
	}
	return false;
}
