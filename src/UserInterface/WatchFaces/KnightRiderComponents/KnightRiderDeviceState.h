#pragma once

#define KNIGHTRIDER_DEVCIESTATE_LOCKED 1
#define KNIGHTRIDER_DEVCIESTATE_DISPLAYON 2;
#define KNIGHTRIDER_DEVCIESTATE_STOPWATCH_RUNNING 4;

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class KnightRiderDeviceState : public Component {

	public:

		void render();


	protected:

		uint8_t const POS_Y = 160;

		uint8_t prevBitMask;

		void renderButton(uint8_t col, char* text, bool state);

		uint8_t getDeviceStateBitMask();

};
