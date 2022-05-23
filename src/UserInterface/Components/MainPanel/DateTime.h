#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/DateTime/Date.h"
#include "UserInterface/Components/MainPanel/DateTime/Time.h"

class DateTime : public MainComponent {

	public:

		void setShouldReRender(bool shouldReRender);
		void render();
		DateTime();

	protected:

		Date *_date;
		Time *_time;

};
