#include "config.h"

#include <LilyGoWatch.h>

#include "SplashScreen.h"
#include "Core/Hardware/MotorController.h"
#include "Core/Hardware/Display.h"
#include "UserInterface/BackgroundRenderer.h"

void SplashScreen::show() {
	MotorController::vibrate(1);

	BackgroundRenderer::renderImage(BACKGROUND_LOGO);
	delay(3000);
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
		TFT_WIDTH,
		TFT_HEIGHT,
		COLOR_BACKGROUND
	);
}

