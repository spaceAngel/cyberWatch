#pragma once

#include "UserInterface/Components/Component.h"

class ProgressBar : public Component {

	public:

		void render(int32_t value);

		ProgressBar(uint8_t y, uint8_t maxValue, long color);

	protected:

		int32_t const BAR_START = 92;
		int32_t const BAR_HEIGHT = 14;

		int32_t y;
		int32_t maxValue;
		int32_t prevValue;
		long color;

};

