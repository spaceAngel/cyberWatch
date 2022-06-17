#pragma once

#include "UserInterface/Components/MainComponent.h"

class NeonCircle : public MainComponent {

	public:

		void render(int32_t value);
		NeonCircle(uint8_t x, uint8_t y, uint8_t maxValue, long color);

	protected:

		int32_t x, y;
		long color;
		int32_t prevValue;
		int32_t maxValue;

};
