#include "config.h"

#include "KnightRiderSpeaker.h"

#include <LilyGoWatch.h>

void KnightRiderSpeaker::render() {
	this->ticks++;
	if (this->ticks == 6) {
		this->ticks = 0;
		uint8_t rows;
		while( ( rows = rand() ) > 4 )  {}
		TTGOClass::getWatch()->tft->fillRect(
			- 3 +  (TTGOClass::getWatch()->tft->width() - 5 - CELL_WIDTH * 3) / 2,
			0,
			18 + CELL_WIDTH * 3,
			112,
			COLOR_BACKGROUND
		);
		if (rows > 0) {
			this->renderSpeakerCol(2, rows + 1);
			if (rows > 1) {
				this->renderSpeakerCol(1, rows);
				this->renderSpeakerCol(3, rows);
			}
		}
	}
}

void KnightRiderSpeaker::renderSpeakerCol(uint8_t col, uint8_t value) {
	for (uint8_t i = 0; i < value; i++) {
		this->renderSpeakerCell( i, col);
		this->renderSpeakerCell(0 - i, col);
	}
}

void KnightRiderSpeaker::renderSpeakerCell(int8_t row, uint8_t col) {
	uint8_t posX = 3 + (TTGOClass::getWatch()->tft->width() - CELL_WIDTH * 3.5) / 2;
	TTGOClass::getWatch()->tft->fillRect(
		posX + (col  - 1) * CELL_WIDTH + (col - 1) * 3,
		65 + row * (CELL_HEIGHT + 3),
		CELL_WIDTH,
		CELL_HEIGHT,
		TFT_RED
	);
}
