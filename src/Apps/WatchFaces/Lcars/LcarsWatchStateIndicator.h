#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class LcarsWatchStateIndicator : public Component {
	public:
		void render();

		LcarsWatchStateIndicator() {};

	protected:
		bool prevAlarm = false;
		bool prevDisplay = false;
		bool prevLock = false;


};
