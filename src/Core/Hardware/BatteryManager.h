#pragma once

#include "config.h"

class BatteryManager {

	public:

		static BatteryManager *getInstance();

		uint8_t getCapacity();

		bool isCharging();

		bool handleCabelPlugInIRQ();

		bool handleCabelPlugRemoveIRQ();

		void energyConsumptionSavingsSettings();

	protected:

			static BatteryManager *inst;

			int lastCapacity = 0;

			BatteryManager();
};
