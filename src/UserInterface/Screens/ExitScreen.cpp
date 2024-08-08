#include "config.h"

#include "ExitScreen.h"

#include <LilyGoWatch.h>

#include "SplashScreenImage.h"

void ExitScreen::show() {

	TTGOClass::getWatch()->tft->pushImage(
		0,
		0,
		240,
		240,
		SPLASHSCREEN_IMAGE
	);
}
