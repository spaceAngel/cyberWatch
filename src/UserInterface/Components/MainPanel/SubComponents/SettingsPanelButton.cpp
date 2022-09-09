#include "config.h"

#include "SettingsPanelButton.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Esp32.h"

SettingsPanelButton::SettingsPanelButton(
	char *btnText,
	uint8_t col,
	uint8_t row,
	std::function<bool(void)> isActiveFunc,
	std::function<void(void)> handleTouchFunc
) {
	this->btnText = btnText;
	this->col = col;
	this->row = row;
	this->isActiveFunc = isActiveFunc;
	this->handleTouchFunc = handleTouchFunc;
}

uint8_t SettingsPanelButton::getX() {
	return 5 + (this->col == (uint8_t) 1 ? 0 : (TTGOClass::getWatch()->tft->width() / 2));
}

uint8_t SettingsPanelButton::getY() {
	return 13 + (((int32_t)this->row - 1) * 71);
}

uint8_t SettingsPanelButton::getWidth() {
	return (TTGOClass::getWatch()->tft->width() / 2) - 10;
}

uint8_t SettingsPanelButton::getHeight() {
	return 54;
}

void SettingsPanelButton::render() {
	if (
		this->prevValue == this->isActiveFunc()
		&& this->shouldReRender() == false
	) {
		return;
	}

	this->prevValue = this->isActiveFunc();
	TTGOClass::getWatch()->tft->fillRect(
		this->getX(),
		this->getY(),
		this->getWidth(),
		this->getHeight(),
		COLOR_BACKGROUND
	);

	TTGOClass::getWatch()->tft->fillRect(
		this->getX() + 22,
		this->getY(),
		this->getWidth() - 44 ,
		this->getHeight() + 1,
		COLOR_MAIN_1
	);
	TTGOClass::getWatch()->tft->fillCircle(
		this->getX() + 25,
		this->getY() + (this->getHeight() / 2),
		this->getHeight() / 2,
		COLOR_MAIN_1
	);
	TTGOClass::getWatch()->tft->fillCircle(
		this->getX() + this->getWidth() - 25,
		this->getY() + (this->getHeight() / 2),
		this->getHeight() / 2,
		COLOR_MAIN_1
	);

	if (this->isActiveFunc() == false) {
		TTGOClass::getWatch()->tft->fillRect(
			this->getX() + 23,
			this->getY() + 1,
			this->getWidth() - 46,
			this->getHeight() - 1,
			COLOR_BACKGROUND
		);
		TTGOClass::getWatch()->tft->fillCircle(
			this->getX() + 25,
			this->getY() + (this->getHeight() / 2),
			(this->getHeight() / 2) - 1,
			COLOR_BACKGROUND
		);
		TTGOClass::getWatch()->tft->fillCircle(
			this->getX() + this->getWidth() - 25,
			this->getY() + (this->getHeight() / 2),
			(this->getHeight() / 2) - 1,
			COLOR_BACKGROUND
		);
	}
	TTGOClass::getWatch()->tft->setTextColor(this->isActiveFunc() ? COLOR_BACKGROUND : COLOR_MAIN_1);
	TTGOClass::getWatch()->tft->drawString(
		this->btnText,
		this->getX() + (this->getWidth() - TTGOClass::getWatch()->tft->textWidth(this->btnText)) / 2,
		2 + this->getY() + (this->getHeight() - TTGOClass::getWatch()->tft->fontHeight()) / 2
	);
	TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
}

void SettingsPanelButton::handleTouch() {
	this->handleTouchFunc();
}
