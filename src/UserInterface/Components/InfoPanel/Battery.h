#pragma once

#include "config.h"

#include "System/BatteryManager.h"

class Battery {

	public:

		void render();

	protected:

		uint8_t prevCapacity = 101;
		bool prevChargingState = false;

		const uint POS_X = 15;
		const uint POS_Y = 150;

		void renderBatteryIcon(uint8_t capacity);
		void renderChargingIcon();
};
