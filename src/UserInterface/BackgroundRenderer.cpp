#include "BackgroundRenderer.h"

#include "config.h"
#include <LilyGoWatch.h>
#include <Arduino.h>

#include "BackgroundImages/SplashScreenImage.h"
#include "BackgroundImages/AnalogFace.h"
#include "BackgroundImages/LcarsBackground.h"
#include "BackgroundImages/VaporwaveSunset.h"

void BackgroundRenderer::renderImage(uint8_t image) {
	BackgroundRenderer::renderImage(image, 0, 0);
}

void BackgroundRenderer::renderImage(uint8_t image, uint8_t x, uint8_t y) {
	TTGOClass::getWatch()->tft->setSwapBytes(true);
	switch (image) {
		case BACKGROUND_LOGO:
			TTGOClass::getWatch()->tft->pushImage(x, y, 240, 240, DATA_SPLASHSCREEN_IMAGE);
		break;
		case BACKGROUND_WATCH_ANALOG:
			TTGOClass::getWatch()->tft->pushImage(x, y, 240, 240, DATA_WATCHFACE_ANALOG);
		break;
		case BACKGROUND_WATCH_LCARS:
			TTGOClass::getWatch()->tft->pushImage(x, y, 240, 240, DATA_WATCHFACE_LCARS);
		break;
		case BACKGROUND_WATCH_VAPORWAVE:
			TTGOClass::getWatch()->tft->pushImage(x, y, 240, 240, DATA_WATCHFACE_VAPORWAVE);
		break;

	}
}