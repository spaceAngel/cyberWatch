#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class StepCounter : public Component {

	public:

		void render();

	protected:

		const uint8_t POS_X = 20;
		const uint8_t POS_Y = 180;

		uint prevStepCount = 0;

		void clearDisplay();

};
