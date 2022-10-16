#include "config.h"

#include "Display.h"

#include <LilyGoWatch.h>

#include "UserInterface/UserInterfaceManager.h"
#include "Utils/TimeUtil.h"

Display *Display::inst;

Display *Display::getInstance() {
	if (Display::inst == nullptr) {
		Display::inst = new Display();
	}
	return Display::inst;
}

void Display::init() {
	TTGOClass::getWatch()->openBL();
	this->setAdjust(DISPLAY_ADJUST);
	TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
}

bool Display::isDisplayOn() {
	return this->lastOn > 0;
}

void Display::turnDisplayOff() {
	if (isDisplayOn()) {
		TTGOClass::getWatch()->displaySleep();
		TTGOClass::getWatch()->bl->off();
		this->lastOn = 0;
	}
}

void Display::turnDisplayOn() {
	if (!isDisplayOn()) {
		UserInterfaceManager::getInstance()->render();
		TTGOClass::getWatch()->bl->on();
		TTGOClass::getWatch()->displayWakeup();
		this->lastOn = TimeUtil::getCurrentTimeInSeconds();
	}
}

void Display::setAdjust(uint8_t adjustPercent) {
	uint8_t adjust = ((ADJUST_MAX - ADJUST_MIN) * adjustPercent) / 100;
	TTGOClass::getWatch()->bl->adjust(ADJUST_MIN + adjust);
	this->adjustPercent = adjustPercent;
}

uint8_t Display::getAdjust() {
	return this->adjustPercent;
}
