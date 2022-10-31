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
		TTGOClass::getWatch()->tft->width(),
		TTGOClass::getWatch()->tft->height(),
		COLOR_BACKGROUND
	);
}

void SplashScreen::renderLoadingBar() {
	uint margin = 20;
	//"loading effect" progressbar
	for (uint i = margin; i < (TTGOClass::getWatch()->tft->width() - (margin * 2)); i++) {
		TTGOClass::getWatch()->tft->fillRect(
			margin,
			TTGOClass::getWatch()->tft->height() - 60,
			i,
			10,
			COLOR_MAIN_1
		);
		delay(25);
	}
}
