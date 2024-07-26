#include "BlankScreen.h"

#include "config.h"
#include <LilyGoWatch.h>

void BlankScreen::render() {
	if (this->shouldReRender()) {
		TTGOClass::getWatch()->tft->fillScreen(COLOR_BACKGROUND);
		this->setShouldReRender(false);
	}
}