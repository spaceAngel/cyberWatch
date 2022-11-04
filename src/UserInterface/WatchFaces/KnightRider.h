#pragma once

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/WatchFaces/Components/KnightRiderButton.h"

class KnightRider : public MainComponent {

	public:

		void render();
		void setShouldReRender(bool shouldReRender);

		KnightRider();

	protected:

		uint8_t const CELL_WIDTH = 18;
		uint8_t const CELL_HEIGHT = 10;

		uint8_t ticks = 0;

		KnightRiderButton *buttons[6];

		void renderSpeaker();
		void renderSpeakerCol(uint8_t col, uint8_t value);
		void renderSpeakerCell(int8_t row, uint8_t col);

		void renderDataCells();


};
