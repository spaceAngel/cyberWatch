#pragma once

#include "config.h"

#include "Core/Hardware/BatteryManager.h"
#include "UserInterface/Components/Component.h"

class Battery : public Component {

	public:

		void render();

		Battery(uint8_t x, uint8_t y, bool showCapacity) {
			this->posX = x;
			this->posY = y;
			this->showCapacity = showCapacity;
		}

	protected:

		uint8_t prevCapacity = 101;
		bool prevChargingState = false;

//		const uint POS_X = 15;
//		const uint POS_Y = 150;

		uint8_t posX;
		uint8_t posY;

		bool showCapacity;

		void renderBatteryIcon(uint8_t capacity);
		void renderCapacity(uint8_t capacity);
};
