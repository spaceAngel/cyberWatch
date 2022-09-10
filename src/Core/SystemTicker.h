#pragma once

#include <Arduino.h>

class SystemTicker {

	public:

		static SystemTicker *getInstance();

		void tickWakedUp();
		void tickSleep();

		bool isTickFor(uint16_t tickCount);


	protected:

		static SystemTicker *inst;

		uint16_t ticks = 0;

		SystemTicker() {

		}
};
