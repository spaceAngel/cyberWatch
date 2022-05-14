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

			static BatteryManager *_inst;

			long _lastActivity;

			BatteryManager();
};
