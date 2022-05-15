#pragma once

#include "UserInterface/Components/InfoPanel/StepCounter.h"
#include "UserInterface/Components/InfoPanel/Battery.h"

class InfoPanel {

	public:

		InfoPanel() {
			_battery = new Battery();
			_stepCounter = new StepCounter();
		}


		void render();

	protected:

		Battery *_battery;
		StepCounter *_stepCounter;

};
