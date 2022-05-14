#pragma once

#include "config.h"

#include "System/BatteryManager.h"

class Battery {

	public:

		void render();

	protected:

		int _prevCapacity = 101;
		bool _prevChargingState = false;

		const uint POS_X = 15;
		const uint POS_Y = 140;

		void _renderBatteryIcon(int capacity);
		void _renderChargingIcon();
};
