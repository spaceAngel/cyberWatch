#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class Time : public Component {

	public:

		void render();

	protected:

		uint8_t prevMinute = 99;
		const uint8_t POS_Y = 72;

};
