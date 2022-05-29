#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"

class Time : public MainComponent {

	public:

		void render();

	protected:

		uint8_t prevMinute = 99;
		const uint8_t POS_Y = 72;

};
