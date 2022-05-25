#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/DateTime/Date.h"
#include "UserInterface/Components/MainPanel/DateTime/Time.h"
#include "UserInterface/Components/MainPanel/DateTime/AnalogClocks.h"

class DateTime : public MainComponent {

	public:

		bool handleVerticalSwipe(int8_t vector);
		void setShouldReRender(bool shouldReRender);
		void render();
		DateTime();

	protected:

		Date *_date;
		Time *_time;
		AnalogClocks *_clocks;

		bool _isDigital = false;

};
