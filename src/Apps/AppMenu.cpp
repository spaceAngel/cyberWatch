#include "config.h"

#include "AppMenu.h"

#include <LilyGoWatch.h>
#include "AppMenu/appIconStopwatch.h"
#include "AppMenu/appIconCalendar.h"
#include "AppMenu/appIconAlarm.h"
#include "AppMenu/appIconSettings.h"
#include "AppMenu/appIconInfo.h"
#include "AppMenu/appIconBulb.h"
#include "AppMenu/appIconCalc.h"

#include "UserInterface/AppRunner.h"
#include "Alarm.h"
#include "Calendar.h"
#include "StopWatch.h"
#include "SettingsPanel.h"
#include "AboutPanel.h"
#include "Flashlight.h"
#include "Calculator.h"

void AppMenu::render() {
	if (this->shouldReRender()) {
		this->renderIcon(APPICON_ALARM, 1,1);
		this->renderIcon(APPICON_STOPWATCH, 2,1);
		this->renderIcon(APPICON_CALENDAR, 3,1);

		this->renderIcon(APPICON_BULB, 1,2);
		this->renderIcon(APPICON_CALC, 2,2);

		this->renderIcon(APPICON_INFO, 2,3);
		this->renderIcon(APPICON_SETTINGS, 3,3);
		this->setShouldReRender(false);
	}
}

void AppMenu::renderIcon(const uint16_t *icon, uint8_t x, uint8_t y) {
	TTGOClass::getWatch()->tft->setSwapBytes(true);
	TTGOClass::getWatch()->tft->pushImage(
		80 * (x-1),
		80 * (y-1),
		80,
		80,
		icon
	);
}

bool AppMenu::handleTouch(uint8_t x, uint8_t y) {
	uint8_t cellWidth = TFT_WIDTH / 3;
	uint8_t cellHeight = TFT_HEIGHT / 3;
	uint8_t posX = (x/cellWidth) + 1;
	uint8_t posY = (y/cellHeight) + 1;
	if (posX == 1 && posY == 1) {AppRunner::getInstance()->setAppOnTop(new Alarm());}
	if (posX == 2 && posY == 1) {AppRunner::getInstance()->setAppOnTop(new StopWatch());}
	if (posX == 3 && posY == 1) {AppRunner::getInstance()->setAppOnTop(new Calendar());}
	if (posX == 1 && posY == 2) {AppRunner::getInstance()->setAppOnTop(new Flashlight());}
	if (posX == 2 && posY == 2) {AppRunner::getInstance()->setAppOnTop(new Calculator());}
	if (posX == 2 && posY == 3) {AppRunner::getInstance()->setAppOnTop(new AboutPanel());}
	if (posX == 3 && posY == 3) {AppRunner::getInstance()->setAppOnTop(new SettingsPanel());}
	return false;
}

AppMenu::AppMenu() {
}

bool AppMenu::handlePEKShort() {
	AppRunner::getInstance()->setToDefaultApp();
	return true;
}

bool AppMenu::onSwipeDown() {
	AppRunner::getInstance()->setToDefaultApp();
	return true;
}

