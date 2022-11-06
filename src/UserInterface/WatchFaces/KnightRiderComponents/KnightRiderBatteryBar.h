#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"

class KnightRiderBatteryBar : public MainComponent{

	public:

		void render();

	protected:

		uint8_t const POS_Y = 121;
		uint8_t const HEIGHT = 7;

		uint8_t prevCapacity = 101;
		void renderBar(uint8_t capacity);
};