#include "App.h"

#include "UserInterface/AppRunner.h"

bool App::handlePEKShort() {
	AppRunner::getInstance()->setToDefaultApp();
	return true;
}

void App::renderTitle(const char *title) {
	TTGOClass::getWatch()->tft->drawString(
		title,
		(TFT_WIDTH - TTGOClass::getWatch()->tft->textWidth(title)) / 2,
		APP_POSITION_TOP
	);
}