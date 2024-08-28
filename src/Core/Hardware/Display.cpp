#include "config.h"

#include "Display.h"

#include <LilyGoWatch.h>

#include "UserInterface/UserInterfaceManager.h"
#include "Utils/TimeUtil.h"
#include "Core/Registry.h"

Display *Display::inst;

Display *Display::getInstance() {
	if (Display::inst == nullptr) {
		Display::inst = new Display();
	}
	return Display::inst;
}

void Display::init() {
	TTGOClass::getWatch()->openBL();
	uint adjust = Registry::getInstance()->getValue(REGISTRY_DISPLAY_ADJUST, DISPLAY_ADJUST);
	if (
		(adjust > 0)
		&& (adjust <= 100)
	) {
		this->setAdjust(adjust);
	} else {
		this->setAdjust(DISPLAY_ADJUST);
	}

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
		TTGOClass::getWatch()->power->setPowerOutPut(AXP202_LDO2, false);
	}
}

void Display::turnDisplayOn() {
	if (!isDisplayOn()) {
		UserInterfaceManager::getInstance()->render();
		TTGOClass::getWatch()->bl->on();
		TTGOClass::getWatch()->displayWakeup();
		this->lastOn = TimeUtil::getCurrentTimeInSeconds();
		TTGOClass::getWatch()->power->setPowerOutPut(AXP202_LDO2, true);
	}
}

void Display::setAdjust(uint8_t adjustPercent) {
	Registry::getInstance()->setValue(REGISTRY_DISPLAY_ADJUST, adjustPercent);
	uint8_t adjust = ((ADJUST_MAX - ADJUST_MIN) * adjustPercent) / 100;
	TTGOClass::getWatch()->bl->adjust(ADJUST_MIN + adjust);
	this->adjustPercent = adjustPercent;
}

uint8_t Display::getAdjust() {
	return this->adjustPercent;
}

void Display::resetTypographySettings() {
	TTGOClass::getWatch()->tft->setTextFont(4); //reset to default
	TTGOClass::getWatch()->tft->setTextSize(1); //reset to default
	TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
}