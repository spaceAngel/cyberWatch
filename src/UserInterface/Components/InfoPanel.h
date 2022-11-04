#pragma once

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/InfoPanel/StepCounter.h"
#include "UserInterface/Components/Icons/Battery.h"
#include "UserInterface/Components/Icons/RunningStopWatch.h"
#include "UserInterface/Components/Icons/DisplayOn.h"
#include "UserInterface/Components/Icons/Lock.h"
#include "UserInterface/Components/Icons/Charger.h"

class InfoPanel : public MainComponent{

	public:

		InfoPanel() {
			this->battery = new Battery(15, 150, true);
			this->charger = new Charger(70, 153);
			this->stepCounter = new StepCounter();
			this->runningStopWatch = new RunningStopWatch();
			this->displayOn = new DisplayOn();
			this->lock = new Lock();
		}

		void render();
		void setShouldReRender(bool shouldReRender);

	protected:

		Battery *battery;
		StepCounter *stepCounter;
		RunningStopWatch *runningStopWatch;
		DisplayOn *displayOn;
		Lock *lock;
		Charger *charger;


};
