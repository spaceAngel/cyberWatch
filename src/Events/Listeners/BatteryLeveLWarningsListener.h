#pragma once

#include "Events/EventListener.h"

class BatteryLeveLWarningsListener : public EventListener {

	public:

		virtual bool listen(uint8_t event);

		virtual void handle();

		BatteryLeveLWarningsListener() {

		}

	protected:

		uint8_t batteryLowWarnVibrateOnLevel = 101;
};
