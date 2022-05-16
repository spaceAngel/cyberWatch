#pragma once

#include <Arduino.h>

class StepCounter {

	public:

		enum {

		};

		StepCounter();
		void render();

	protected:

		const uint8_t POS_X = 20;
		const uint8_t POS_Y = 170;

		uint _prevStepCount = 0;

		void _clearDisplay();
		void _renderIcon();

};
