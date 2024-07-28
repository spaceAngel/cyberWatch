#include "config.h"
#include "Logo.h"
#include <LilyGoWatch.h>

void Logo::render() {
	TTGOClass::getWatch()->tft->setTextFont(2);
	TTGOClass::getWatch()->tft->setTextSize(3);

	TTGOClass::getWatch()->tft->drawString(
		APP_NAME,
			(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth(APP_NAME)) / 2,
			(RESOLUTION_HEIGHT / 2 )- TTGOClass::getWatch()->tft->fontHeight()
		);

		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->drawString(
			APP_VERSION,
		(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth(APP_VERSION)) / 2,
        RESOLUTION_HEIGHT / 2
	);
};

