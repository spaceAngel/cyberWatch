#include "config.h"

#include "SettingsPanel.h"
#include "UserInterface/UserInterfaceManager.h"
#include "UserInterface/Icons/LightBulb.h"
#include "Environment/AppSettings.h"
#include "Core/Hardware/Display.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Esp32.h"
#include "Apps/AboutPanel.h"
#include "UserInterface/Screens/MainScreen.h"

void SettingsPanel::render() {
	if (
		this->lastMask != AppSettings::getInstance()->getSettingsByteMask()
		|| this->shouldReRender()
	) {
		Esp32::getInstance()->runWithCpuSpeedHigh(
			[this]() {
				this->renderAdjustBar();
				for (int32_t i = 0; i <= BUTTONS; i++) {
					this->buttons[i]->render();
				}
			}
		);
		this->setShouldReRender(false);
		this->lastMask = AppSettings::getInstance()->getSettingsByteMask();
	}
}

bool SettingsPanel::controlModeIsTouch() {
	return true;
}

bool SettingsPanel::handleTouch(uint8_t x, uint8_t y) {
	if (y >= ADJUSTBAR_POSY && y <= ADJUSTBAR_POSY + ADJUSTBAR_HEIGHT) {
		this->handleTouchAdjustbar(x);
	} else {
		this->handleTouchButtons(x, y);
	}
	return false;
}

void SettingsPanel::handleTouchButtons(uint8_t x, uint8_t y) {
	for (int32_t i = 0; i <= BUTTONS; i++) {
		if (
			(x > this->buttons[i]->getX())
			&& (x < this->buttons[i]->getX() + this->buttons[i]->getWidth())
			&& (y > this->buttons[i]->getY())
			&& (y < this->buttons[i]->getY() + this->buttons[i]->getHeight())
		) {
			this->buttons[i]->handleTouch();
		}
	}
}

void SettingsPanel::handleTouchAdjustbar(uint8_t x) {
	uint8_t adjustWidthFull = (TTGOClass::getWatch()->tft->width() - (10 * 2)) - (ADJUSTBAR_HEIGHT);
	int adjustPercent = (x - 20 - (ADJUSTBAR_HEIGHT)) * 100  / adjustWidthFull;
	adjustPercent = max(0, adjustPercent);
	Display::getInstance()->setAdjust(adjustPercent);
	this->setShouldReRender(true);
}

void SettingsPanel::setShouldReRender(bool shouldReRender) {
	for (int32_t i = 0; i <= BUTTONS; i++) {
		this->buttons[i]->setShouldReRender(shouldReRender);
	}
	App::setShouldReRender(shouldReRender);
}

void SettingsPanel::renderAdjustBar() {

	uint8_t margin = 10;
	TTGOClass::getWatch()->tft->fillCircle(
		margin + (ADJUSTBAR_HEIGHT / 2),
		ADJUSTBAR_POSY + (ADJUSTBAR_HEIGHT / 2),
		(ADJUSTBAR_HEIGHT / 2),
		COLOR_MAIN_1
	);

	TTGOClass::getWatch()->tft->fillCircle(
		TTGOClass::getWatch()->tft->width() - margin - (ADJUSTBAR_HEIGHT / 2),
		ADJUSTBAR_POSY + (ADJUSTBAR_HEIGHT / 2),
		(ADJUSTBAR_HEIGHT / 2),
		COLOR_MAIN_1
	);

	uint8_t adjustWidthFull = (TTGOClass::getWatch()->tft->width() - (margin * 2)) - (ADJUSTBAR_HEIGHT);
	uint8_t adjustWidth = (adjustWidthFull *Display::getInstance()->getAdjust()) / 100;
	TTGOClass::getWatch()->tft->fillRect(
		margin + (ADJUSTBAR_HEIGHT / 2),
		ADJUSTBAR_POSY,
		adjustWidthFull,
		ADJUSTBAR_HEIGHT,
		COLOR_BACKGROUND
	);
	TTGOClass::getWatch()->tft->fillRect(
		margin + (ADJUSTBAR_HEIGHT / 2),
		ADJUSTBAR_POSY,
		adjustWidth,
		ADJUSTBAR_HEIGHT,
		COLOR_MAIN_1
	);
	for (uint8_t i = 0; i <= 10; i++) {
		TTGOClass::getWatch()->tft->fillRect(
			margin + (ADJUSTBAR_HEIGHT / 2) + i * (adjustWidthFull / 10),
			ADJUSTBAR_POSY,
			3,
			ADJUSTBAR_HEIGHT,
			COLOR_BACKGROUND
		);
	}
}

bool SettingsPanel::handleLongTouch(uint8_t x, uint8_t y) {
	MainScreen::getInstance()->setAppOnTop(new AboutPanel());
	return true;
}

bool SettingsPanel::handlePEKShort() {
	MainScreen::getInstance()->setToDefaultApp();
	return true;
}