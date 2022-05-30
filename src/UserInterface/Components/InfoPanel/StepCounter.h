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
		const uint8_t POS_Y = 180;

		uint prevStepCount = 0;

		void clearDisplay();
		void renderIcon();

};
