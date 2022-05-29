#pragma once

#include "UserInterface/Components/InfoPanel/StepCounter.h"
#include "UserInterface/Components/InfoPanel/Battery.h"
#include "UserInterface/Components/InfoPanel/RunningStopWatch.h"

class InfoPanel {

	public:

		InfoPanel() {
			this->battery = new Battery();
			this->stepCounter = new StepCounter();
			this->runningStopWatch = new RunningStopWatch();
		}

		void render();

	protected:

		Battery *battery;
		StepCounter *stepCounter;
		RunningStopWatch *runningStopWatch;

};
