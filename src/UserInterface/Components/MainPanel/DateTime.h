#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/DateTime/AnalogClocks.h"
#include "UserInterface/Components/MainPanel/DateTime/DigitalClocks.h"

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
		DigitalClocks *_digital;;

		bool _isDigital = false;

};
