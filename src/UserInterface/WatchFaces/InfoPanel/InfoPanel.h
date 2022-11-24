#pragma once

#include "UserInterface/Components/Component.h"
#include "UserInterface/WatchFaces/InfoPanel/StepCounter.h"
#include "UserInterface/Components/Icons/Battery.h"
#include "UserInterface/Components/Icons/RunningStopWatch.h"
#include "UserInterface/Components/Icons/DisplayOn.h"
#include "UserInterface/Components/Icons/Lock.h"
#include "UserInterface/Components/Icons/Charger.h"
#include "UserInterface/Components/Icons/AlarmOn.h"

class InfoPanel : public Component{

	public:

		InfoPanel() {
			this->battery = new Battery(15, 150, true);
			this->charger = new Charger(70, 153);
			this->stepCounter = new StepCounter();
			this->runningStopWatch = new RunningStopWatch();
			this->displayOn = new DisplayOn();
			this->lock = new Lock();
			this->alarmOn = new AlarmOn();
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
		AlarmOn *alarmOn;


};
