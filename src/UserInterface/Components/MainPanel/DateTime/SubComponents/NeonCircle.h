#pragma once

#include "UserInterface/Components/MainComponent.h"

class NeonCircle : public MainComponent {

	public:

		void render(uint8_t value);
		NeonCircle(uint8_t x, uint8_t y, uint8_t maxValue, long color);

	protected:

		uint8_t x, y;
		long color;
		uint8_t prevValue;
		uint8_t maxValue;

};
