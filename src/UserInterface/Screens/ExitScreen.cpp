#include "config.h"

#include "ExitScreen.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/Logo.h"

void ExitScreen::show() {

	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		RESOLUTION_WIDTH,
		RESOLUTION_HEIGHT,
		COLOR_BACKGROUND
	);

	Logo *logo = new Logo();
	logo->render();

	char message[20] = "leaving	 matrix";
	TTGOClass::getWatch()->tft->drawString(
		message,
		(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth(message)) / 2,
		RESOLUTION_HEIGHT - 60
	);
}

