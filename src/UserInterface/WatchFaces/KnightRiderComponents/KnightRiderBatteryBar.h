#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class KnightRiderBatteryBar : public Component{

	public:

		void render();

	protected:

		uint8_t const POS_Y = 121;
		uint8_t const HEIGHT = 7;

		uint8_t prevCapacity = 101;
		bool wasCharging = false;

		void renderBar(uint8_t capacity);
		void renderChargingIcon(bool chargingState);
};
