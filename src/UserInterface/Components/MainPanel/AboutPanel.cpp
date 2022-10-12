#include "config.h"

#include "AboutPanel.h"

#include <LilyGoWatch.h>
#include "Environment/compilationdata.h"

void AboutPanel::render() {

	TTGOClass::getWatch()->tft->drawString(
		APP_VERSION,
		(TTGOClass::getWatch()->tft->width() / 4) - (TTGOClass::getWatch()->tft->textWidth(APP_VERSION) / 2),
		this->calculatePosY(0, false)
	);
	TTGOClass::getWatch()->tft->drawString(
		compilationCommit,
		(TTGOClass::getWatch()->tft->width() / 2) - 10,
		this->calculatePosY(0, false)
	);
	TTGOClass::getWatch()->tft->drawString(compilationDate, 5, this->calculatePosY(1, false));

}

uint8_t AboutPanel::calculatePosY(uint8_t row, bool shifted) {
	return (shifted ? 30 : 15)
	+ (TTGOClass::getWatch()->tft->fontHeight() * (row * 1.1));
}

AboutPanel::AboutPanel() {

}

