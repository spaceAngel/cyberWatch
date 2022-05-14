#pragma once

#include <Arduino.h>

class Time {

	public:

		void render();

	protected:

		uint _prevMinute = 99;
		const uint POS_Y = 72;

};
