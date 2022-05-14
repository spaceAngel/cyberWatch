#include "config.h"

#include <LilyGoWatch.h>

#include "Display.h"

#include "Screens/MainScreen.h"
#include "Screens/SplashScreen.h"
#include "Screens/ExitScreen.h"
#include "Utils/TimeUtil.h"

Display *Display::_inst;


Display *Display::getInstance() {
	if (Display::_inst == nullptr) {
		Display::_inst = new Display();
	}
	return Display::_inst;
}

void Display::showSplashScreen() {
	SplashScreen *screen = new SplashScreen();
	screen->show();
}

void Display::showExitScreen() {
	ExitScreen *screen = new ExitScreen();
	screen->show();
}

void Display::init() {
	TTGOClass::getWatch()->openBL();
	TTGOClass::getWatch()->bl->adjust(DISPLAY_ADJUST);
	TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
}

void Display::render() {
	MainScreen::getInstance()->render();
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
		render();
		TTGOClass::getWatch()->bl->on();
		TTGOClass::getWatch()->displayWakeup();
		_lastOn = TimeUtil::getCurrentTimeInSeconds();
	}
}
