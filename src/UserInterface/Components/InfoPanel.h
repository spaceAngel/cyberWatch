#pragma once

#include "UserInterface/Components/InfoPanel/StepCounter.h"
#include "UserInterface/Components/InfoPanel/Battery.h"
#include "UserInterface/Components/InfoPanel/RunningStopWatch.h"

class InfoPanel {

	public:

		InfoPanel() {
			_battery = new Battery();
			_stepCounter = new StepCounter();
			_runningStopWatch = new RunningStopWatch();
		}

		void render();

	protected:

		Battery *_battery;
		StepCounter *_stepCounter;
		RunningStopWatch *_runningStopWatch;

};
