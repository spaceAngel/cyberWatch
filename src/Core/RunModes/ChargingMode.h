#pragma once

#include "RunMode.h"

class ChargingMode : public RunMode {

	public:

		void switchedTo();

		void loop();

	protected:

		const uint8_t HEIGHT = 36;
		const uint8_t POS_Y = 90;

		uint8_t loops = 0;
		uint8_t prevBatteryCapacity = 101;

		void handleCabelConnection();

		void handleEsp32IRQ();

		uint8_t getBattercentageWidth();

};
