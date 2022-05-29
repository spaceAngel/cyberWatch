#pragma once

#include "UserInterface/Components/MainComponent.h"

class ProgressBar : public MainComponent {

	public:

		void render(uint8_t value);

		ProgressBar(uint8_t y, uint8_t maxValue, long color);

	protected:

		uint8_t const BAR_START = 92;
		uint8_t const BAR_HEIGHT = 14;

		uint8_t y;
		uint8_t maxValue;
		uint8_t prevValue;
		long color;

};

