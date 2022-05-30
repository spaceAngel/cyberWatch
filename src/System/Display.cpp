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
	TTGOClass::getWatch()->bl->adjust(DISPLAY_ADJUST);
	TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
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
