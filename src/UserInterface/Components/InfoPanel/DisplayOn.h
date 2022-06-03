#pragma once

#include "config.h"

#include "System/BatteryManager.h"

class DisplayOn {

	public:

		void render();

	protected:

		bool prevState = false;

		const uint POS_X = 170;
		const uint POS_Y = 153;

};
