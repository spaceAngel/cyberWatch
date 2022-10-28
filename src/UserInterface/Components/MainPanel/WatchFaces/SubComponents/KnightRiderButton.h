#pragma once

#include "UserInterface/Components/MainComponent.h"

class KnightRiderButton : public MainComponent {

	public:

		void render(int32_t value);
		KnightRiderButton(uint8_t row, uint8_t col, uint32_t color);

	protected:

		int32_t row, col, color;
		int32_t prevValue;



};
