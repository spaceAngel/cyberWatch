#include "config.h"
#include "KnightRiderButton.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"

void KnightRiderButton::render(int32_t value) {
	if (
		this->prevValue!= value
		|| this->shouldReRender()
	) {
		uint8_t cellWidth = 50;
		uint8_t cellHeight = 29;
		uint8_t posX = col == 1 ? 20 : RESOLUTION_WIDTH - (16 + cellWidth);

		uint posY =  9 + (
			(108 / 3) * (row - 1)
		);
		TTGOClass::getWatch()->tft->fillRoundRect(posX, posY, cellWidth, cellHeight, 10, this->color);

		char str[3];
		(void)snprintf(str, sizeof(str), "%02d", value);

		TTGOClass::getWatch()->tft->setTextFont(1);
		TTGOClass::getWatch()->tft->setTextSize(3);
		TTGOClass::getWatch()->tft->setTextColor(COLOR_BACKGROUND);
		TTGOClass::getWatch()->tft->drawString(
			str,
			posX + 7,
			posY + 4
		);
		Display::getInstance()->resetTypographySettings();
	}

	this->prevValue = value;
	this->setShouldReRender(false);
}

KnightRiderButton::KnightRiderButton(uint8_t row, uint8_t col, uint32_t color) {
	this->col = col;
	this->row = row;
	this->color = color;
}