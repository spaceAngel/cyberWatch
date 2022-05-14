#pragma once

#include "InfoPanelComponents/StepCounter.h"
#include "InfoPanelComponents/Battery.h"

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
