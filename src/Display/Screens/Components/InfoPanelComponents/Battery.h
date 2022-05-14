#pragma once

#include "config.h"

#include "System/BatteryManager.h"

class Battery {

	public:

		void render();

	protected:

		uint8_t _prevCapacity = 101;
		bool _prevChargingState = false;

		const uint POS_X = 15;
		const uint POS_Y = 140;

		void _renderBatteryIcon(uint8_t capacity);
		void _renderChargingIcon();
};
