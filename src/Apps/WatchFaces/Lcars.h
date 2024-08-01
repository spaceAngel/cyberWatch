#pragma once

#include "Apps/WatchFaces/WatchFace.h"
#include "Lcars/LcarsBatteryIndicator.h"
#include "Lcars/LcarsWatchStateIndicator.h"
#include "Lcars/LcarsSteps.h"

class Lcars : public WatchFace {

	public:

		void render();

		Lcars() {
			this->battery = new LcarsBatteryIndicator();
			this->watchState = new LcarsWatchStateIndicator();
			this->steps = new LcarsSteps();
		}

		bool hasInfoPanel() {
			return false;
		}

		void setShouldReRender(bool shouldReRender) {
			this->shouldRerender = shouldReRender;
			this->battery->setShouldReRender(shouldReRender);
			this->watchState->setShouldReRender(shouldReRender);
			this->steps->setShouldReRender(shouldRerender);
		}

		bool shouldReRender() {
			return this->shouldRerender;
		}


	protected:
		uint8_t prevMinute = 99;

		bool shouldRerender = true;

		LcarsBatteryIndicator *battery;
		LcarsWatchStateIndicator *watchState;
		LcarsSteps *steps;

		void renderTime();
		void renderDate();


};
