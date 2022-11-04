#include "config.h"

#include <LilyGoWatch.h>

#include "KnightRider.h"
#include "Core/Hardware/RTC.h"
#include "UserInterface/WatchFaces/Components/KnightRiderButton.h"

void KnightRider::render() {
	uint8_t cellWidth = 24;
	uint8_t cellHeight = 12;

	this->renderDataCells();
	if (this->ticks == 6) {
		this->ticks = 0;
		this->renderSpeaker();
	}
	this->ticks++;
}

void KnightRider::setShouldReRender(bool shouldReRender) {
	for (uint8_t i = 0; i<= 5; i++) {
		this->buttons[i]->setShouldReRender(shouldReRender);
	}
}

void KnightRider::renderSpeaker() {
	uint8_t rows;
	while( ( rows = rand() ) > 4 )  {}
	TTGOClass::getWatch()->tft->fillRect(
		- 3 +  (TTGOClass::getWatch()->tft->width() - 5 - CELL_WIDTH * 3) / 2,
		0,
		18 + CELL_WIDTH * 3,
		150,
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

void KnightRider::renderSpeakerCol(uint8_t col, uint8_t value) {
	for (uint8_t i = 0; i < value; i++) {
		this->renderSpeakerCell( i, col);
		this->renderSpeakerCell(0 - i, col);
	}
}

void KnightRider::renderSpeakerCell(int8_t row, uint8_t col) {
	uint8_t posX = 3 + (TTGOClass::getWatch()->tft->width() - CELL_WIDTH * 3.5) / 2;
	TTGOClass::getWatch()->tft->fillRect(
		posX + (col  - 1) * CELL_WIDTH + (col - 1) * 3,
		70 + row * (CELL_HEIGHT + 3),
		CELL_WIDTH,
		CELL_HEIGHT,
		TFT_RED
	);
}

void KnightRider::renderDataCells() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	this->buttons[0]->render(currentTime.hour);
	this->buttons[1]->render(currentTime.minute);
	this->buttons[2]->render(currentTime.second);
	this->buttons[3]->render(currentTime.day);
	this->buttons[4]->render(currentTime.month);
	this->buttons[5]->render(currentTime.year % 2000);
}

KnightRider::KnightRider() {
	this->buttons[0] = new KnightRiderButton(1, 1, TFT_YELLOW);
	this->buttons[1] = new KnightRiderButton(2, 1, TFT_YELLOW);
	this->buttons[2] = new KnightRiderButton(3, 1, TFT_ORANGE);
	this->buttons[3] = new KnightRiderButton(1, 2, TFT_YELLOW);
	this->buttons[4] = new KnightRiderButton(2, 2, TFT_YELLOW);
	this->buttons[5] = new KnightRiderButton(3, 2, TFT_ORANGE);


}
