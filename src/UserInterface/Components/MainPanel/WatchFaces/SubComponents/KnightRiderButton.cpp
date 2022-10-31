#include "config.h"
#include "KnightRiderButton.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"

void KnightRiderButton::render(int32_t value) {
	if (
		this->prevValue!= value
		|| this->shouldReRender()
	) {
		uint8_t cellWidth = 52;
		uint8_t cellHeight = 37;
		uint8_t posX = col == 1 ? 22 : TTGOClass::getWatch()->tft->width() - (18 + cellWidth);

		uint posY =  9 + (
			(142 / 3) * (row - 1)
		);

		TTGOClass::getWatch()->tft->fillCircle(-4 + posX + cellHeight / 2, posY + cellHeight / 2, cellHeight / 2, this->color);
		TTGOClass::getWatch()->tft->fillCircle(posX + cellWidth - (cellHeight / 2), posY + cellHeight / 2, cellHeight / 2, this->color);
		TTGOClass::getWatch()->tft->fillRect(posX + cellHeight / 2, posY, cellWidth - cellHeight, cellHeight, this->color);

		char str[3];
		(void)snprintf(str, sizeof(str), "%02d", value);
		TTGOClass::getWatch()->tft->setTextFont(1);

		TTGOClass::getWatch()->tft->setTextSize(4);
		TTGOClass::getWatch()->tft->setTextColor(COLOR_BACKGROUND);
		TTGOClass::getWatch()->tft->drawString(
			str,
			posX + 3,
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