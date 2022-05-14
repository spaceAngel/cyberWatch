#pragma once

#include <Arduino.h>

class StepCounter {

	public:

		enum {

		};

		StepCounter();
		void render();

	protected:

		const uint POS_X = 20;
		const uint POS_Y = 170;
		uint _prevStepCount = 0;
		uint _iconRendered = false;

		void _clearDisplay();
		void _renderIcon();

};
