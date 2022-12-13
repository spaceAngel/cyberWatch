#include "App.h"

#include "UserInterface/AppRunner.h"

bool App::handlePEKShort() {
	AppRunner::getInstance()->setToDefaultApp();
	return true;
}

void App::renderTitle(const char *title) {
	TTGOClass::getWatch()->tft->drawString(
		title,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(title)) / 2,
		APP_POSITION_TOP
	);
}