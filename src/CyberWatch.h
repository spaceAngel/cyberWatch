#pragma once

#include "config.h"

class CyberWatch {

	public:
		static CyberWatch *getInstance();

		void init();

		void loop();

		void turnOff();

	protected:

		static CyberWatch *inst;

		CyberWatch();

		void handleCabelConnection();

		void handleEsp32IRQ(bool &PEKshort);

		void sleep();

		void handleWakeupTick();

		void checkIfSleepForbiddenAndMarkAsActive();

		void checkIfTiltIrqAndMarkAsActive();

		void executeLoopActions();

		void executeLoopSleep();

		void executeLoopWakeUp();

};
