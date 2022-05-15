#include "config.h"

#include "Display.h"

#include <LilyGoWatch.h>

#include "UserInterface/UserInterfaceManager.h"
#include "Utils/TimeUtil.h"

Display *Display::_inst;

Display *Display::getInstance() {
	if (Display::_inst == nullptr) {
		Display::_inst = new Display();
	}
	return Display::_inst;
}

void Display::init() {
	TTGOClass::getWatch()->openBL();
	TTGOClass::getWatch()->bl->adjust(DISPLAY_ADJUST);
	TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
}

bool Display::isDisplayOn() {
	return _lastOn > 0;
}

void Display::turnDisplayOff() {
	if (isDisplayOn()) {
		TTGOClass::getWatch()->displaySleep();
		TTGOClass::getWatch()->bl->off();
		_lastOn = 0;
	}
}

void Display::turnDisplayOn() {
	if (!isDisplayOn()) {
		UserInterfaceManager::getInstance()->render();
		TTGOClass::getWatch()->bl->on();
		TTGOClass::getWatch()->displayWakeup();
		_lastOn = TimeUtil::getCurrentTimeInSeconds();
	}
}
