#include "config.h"

#include "SettingsPanelButton.h"

#include <LilyGoWatch.h>

SettingsPanelButton::SettingsPanelButton(
	char *btnText,
	uint8_t col,
	uint8_t row,
	std::function<bool(void)> isActiveFunc,
	std::function<bool(void)> handleTouchFunc
) {
	this->btnText = btnText;
	this->col = col;
	this->row = row;
	this->isActiveFunc = isActiveFunc;
	this->handleTouchFunc = handleTouchFunc;
}

uint8_t SettingsPanelButton::getX() {
	return 5 + (col == 1 ? 0 : (TTGOClass::getWatch()->tft->width() / 2));
}

uint8_t SettingsPanelButton::getY() {
	return 13 + (row - 1) * 71;
}

uint8_t SettingsPanelButton::getWidth() {
	return (TTGOClass::getWatch()->tft->width() / 2) - 10;
}

uint8_t SettingsPanelButton::getHeight() {
	return 62;
}

void SettingsPanelButton::render() {
	TTGOClass::getWatch()->tft->fillRect(
		this->getX(),
		this->getY(),
		this->getWidth(),
		this->getHeight(),
		this->isActiveFunc() ? COLOR_MAIN_1 : COLOR_BACKGROUND
	);
	TTGOClass::getWatch()->tft->setTextColor(this->isActiveFunc() ? COLOR_BACKGROUND : COLOR_MAIN_1);
	TTGOClass::getWatch()->tft->drawString(
		this->btnText,
		this->getX() + (this->getWidth() - TTGOClass::getWatch()->tft->textWidth(this->btnText)) / 2,
		this->getY() + (this->getHeight() - TTGOClass::getWatch()->tft->fontHeight()) / 2
	);
	TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
}

bool SettingsPanelButton::handleTouch() {
	return this->handleTouchFunc();
}
