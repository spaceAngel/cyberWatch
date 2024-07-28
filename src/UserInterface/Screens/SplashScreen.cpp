#include "config.h"

#include <LilyGoWatch.h>

#include "SplashScreen.h"
#include "Core/Hardware/MotorController.h"
#include "UserInterface/Components/Logo.h"
#include "Core/Hardware/Display.h"

void SplashScreen::show() {
	MotorController::vibrate(1);

	Logo *logo = new Logo();
	logo->render();
	this->renderLoadingBar();
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

void SplashScreen::renderLoadingBar() {
	uint margin = 20;
	//"loading effect" progressbar
	for (uint i = margin; i < (RESOLUTION_WIDTH - (margin * 2)); i++) {
		TTGOClass::getWatch()->tft->fillRect(
			margin,
			RESOLUTION_HEIGHT - 60,
			i,
			10,
			COLOR_MAIN_1
		);
		delay(25);
	}
}
