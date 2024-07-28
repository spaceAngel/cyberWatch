#pragma once

#include <Arduino.h>

class KnightRiderSpeaker {

	public:
		void render();

	protected:
		uint8_t const CELL_WIDTH = 18;
		uint8_t const CELL_HEIGHT = 7;

		uint8_t ticks = 0;

		void renderSpeakerCol(uint8_t col, uint8_t value);
		void renderSpeakerCell(int8_t row, uint8_t col);

};
