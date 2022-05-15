#pragma once

#include <Arduino.h>

class Time {

	public:

		void render();

	protected:

		uint8_t _prevMinute = 99;
		const uint8_t POS_Y = 72;

};
