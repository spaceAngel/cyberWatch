#pragma once

#include "RunMode.h"

class MainMode : public RunMode {

	public:

		void switchedTo();

		void loop();

	protected:
		void handleCabelConnection();

		void handleEsp32IRQ(bool &PEKshort);

		void sleep();

		void handleWakeupTick();

		void checkIfTiltIrqAndMarkAsActive();

		void executeLoopActions();

		void executeLoopSleep();

		void executeLoopWakeUp();

		bool isSleepForbidden();

		void turnOff();
};