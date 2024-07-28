#pragma once

#include "UserInterface/Components/Component.h"

class NeonCircle : public Component {

	public:

		void render(int32_t value);
		NeonCircle(uint8_t x, uint8_t y, uint8_t maxValue, long color);

	protected:

		int32_t x, y;
		long color;
		int32_t prevValue;
		int32_t maxValue;

		void renderCircle(int32_t value);

};
