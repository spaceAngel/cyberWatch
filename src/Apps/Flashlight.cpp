#include "config.h"

#include <LilyGoWatch.h>

#include "Flashlight.h"
#include "Core/Hardware/Display.h"
#include "UserInterface/AppRunner.h"

void Flashlight::render() {
	Display::getInstance()->setAdjust(100);
	TTGOClass::getWatch()->tft->fillScreen(TFT_WHITE);
}

bool Flashlight::handlePEKShort() {
	Display::getInstance()->setAdjust(this->displayAdjust);
	AppRunner::getInstance()->setToDefaultApp();
	return true;
}


Flashlight::Flashlight() {
	this->displayAdjust = Display::getInstance()->getAdjust();
}