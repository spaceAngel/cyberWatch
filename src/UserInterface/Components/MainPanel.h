#pragma once

#include "UserInterface/Components/MainPanel/Date.h"
#include "UserInterface/Components/MainPanel/Time.h"
#include "UserInterface/Components/MainPanel/Calendar.h"

class MainPanel {

	public:

		MainPanel() {
			_date = new Date();
			_time = new Time();
			_calendar = new Calendar();
		}

		void render();
		void switchScreen(int vector);

	protected:

		const uint8_t COMPONENT_DATETIME = 1;
		const uint8_t COMPONENT_CALENDAR = 2;

		const uint8_t COMPONENTS = 2;

		uint _currentComponent = COMPONENT_CALENDAR;

		Date *_date;
		Time *_time;
		Calendar *_calendar;

		void _clear();

};
