#pragma once

#include "config.h"

#include "Core/Hardware/BatteryManager.h"

class Charger {

	public:

		void render();

		Charger(uint8_t x, uint8_t y) {
			this->posX = x;
			this->posY = y;
		}

	protected:

		uint8_t posX;
		uint8_t posY;

		bool prevState = false;
		bool prevChargingState = false;

};
