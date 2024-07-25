#include "config.h"

#include "AppMenu.h"

#include <LilyGoWatch.h>
#include "AppMenu/AppIcon.h"
#include "AppMenu/appIconAlarm.h"
#include "AppMenu/appIconStopwatch.h"
#include "AppMenu/appIconCalendar.h"
#include "AppMenu/appIconSettings.h"

#include "UserInterface/AppRunner.h"
#include "Alarm.h"
#include "Calendar.h"
#include "StopWatch.h"
#include "SettingsPanel.h"

void AppMenu::render() {
	if (this->shouldReRender()) {
		uint8_t width = TTGOClass::getWatch()->tft->width() / 3;
		uint8_t height = TTGOClass::getWatch()->tft->height() / 3;
		TTGOClass::getWatch()->tft->drawLine(0, height, TTGOClass::getWatch()->tft->width() , height, COLOR_MAIN_3);
		TTGOClass::getWatch()->tft->drawLine(0, height * 2, TTGOClass::getWatch()->tft->width() , height * 2, COLOR_MAIN_3);
		TTGOClass::getWatch()->tft->drawLine(width, 0, width, TTGOClass::getWatch()->tft->height() , COLOR_MAIN_3);
		TTGOClass::getWatch()->tft->drawLine(width * 2, 0, width *2, TTGOClass::getWatch()->tft->height() , COLOR_MAIN_3);

		this->renderIcon(appIconAlarm, 1,1);
		this->renderIcon(appIconStopwatch, 2,1);
		this->renderIcon(appIconCalendar, 3,1);
		this->renderIcon(appIconSettings, 3,3);
	}
}

void AppMenu::renderIcon(AppIcon icon, uint8_t x, uint8_t y) {
	uint8_t width = TTGOClass::getWatch()->tft->width() / 3;
	uint8_t height = TTGOClass::getWatch()->tft->height() / 3;
	TTGOClass::getWatch()->tft->setSwapBytes(true);
	TTGOClass::getWatch()->tft->pushImage(
		width * (x - 1) + ((width - icon.width) / 2),
		height * (y - 1) + ((height - icon.heigth) / 2),
		icon.width,
		icon.heigth,
		icon.data
	);
}

bool AppMenu::handleTouch(uint8_t x, uint8_t y) {
	uint8_t cellWidth = TTGOClass::getWatch()->tft->width() / 3;
	uint8_t cellHeight = TTGOClass::getWatch()->tft->height() / 3;
	uint8_t posX = (x/cellWidth) + 1;
	uint8_t posY = (y/cellHeight) + 1;
	if (posX == 1 && posY == 1) {AppRunner::getInstance()->setAppOnTop(new Alarm());}
	if (posX == 2 && posY == 1) {AppRunner::getInstance()->setAppOnTop(new StopWatch());}
	if (posX == 3 && posY == 1) {AppRunner::getInstance()->setAppOnTop(new Calendar());}
	if (posX == 3 && posY == 3) {AppRunner::getInstance()->setAppOnTop(new SettingsPanel());}
	return true;
}

AppMenu::AppMenu() {
}