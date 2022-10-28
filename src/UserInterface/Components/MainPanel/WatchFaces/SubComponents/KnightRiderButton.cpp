#include "config.h"
#include "KnightRiderButton.h"

#include <LilyGoWatch.h>

void KnightRiderButton::render(int32_t value) {
	if (
		this->prevValue!= value
		|| this->shouldReRender()
	) {
		uint8_t cellWidth = 62;
		uint8_t cellHeight = 40;
		uint8_t posX = col == 1 ? 14 : TTGOClass::getWatch()->tft->width() - (12 + cellWidth);

		uint posY = 4 + (
			(150 / 3) * (row - 1)
		);

		TTGOClass::getWatch()->tft->fillCircle(-4 + posX + cellHeight / 2, posY + cellHeight / 2, cellHeight / 2, this->color);
		TTGOClass::getWatch()->tft->fillCircle(posX + cellWidth - (cellHeight / 2), posY + cellHeight / 2, cellHeight / 2, this->color);
		TTGOClass::getWatch()->tft->fillRect(posX + cellHeight / 2, posY, cellWidth - cellHeight, cellHeight, this->color);

		char str[3];
		(void)snprintf(str, sizeof(str), "%02d", value);
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->setTextColor(COLOR_BACKGROUND);
		TTGOClass::getWatch()->tft->drawString(
			str,
			posX ,
			posY
		);
		TTGOClass::getWatch()->tft->setTextSize(1);
		TTGOClass::getWatch()->tft->setTextColor(COLOR_MAIN_1);
	}

	this->prevValue = value;
	this->setShouldReRender(false);
}


KnightRiderButton::KnightRiderButton(uint8_t row, uint8_t col, uint32_t color) {
	this->col = col;
	this->row = row;
	this->color = color;
}