#include "config.h"

#include <LilyGoWatch.h>

#include "SplashScreen.h"
#include "Core/Hardware/MotorController.h"
#include "Core/Hardware/Display.h"
#include "SplashScreenImage.h"

void SplashScreen::show() {
	MotorController::vibrate(1);

	TTGOClass::getWatch()->tft->setSwapBytes(true);
	TTGOClass::getWatch()->tft->pushImage(0, 0, 240, 240, SPLASHSCREEN_IMAGE);
	delay(7000);
	this->resetToDefault();
	MotorController::vibrate(1);
	delay(200);
}

void SplashScreen::resetToDefault() {
	//clear display
	Display::getInstance()->resetTypographySettings();
	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		RESOLUTION_WIDTH,
		RESOLUTION_HEIGHT,
		COLOR_BACKGROUND
	);
}

