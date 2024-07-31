#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class LcarsBatteryIndicator : public Component {
	public:
		void render();

		LcarsBatteryIndicator() {};

	protected:
		bool prevCharging = false;
		uint8_t prevCapacity= 101;

};
