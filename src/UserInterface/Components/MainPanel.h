#pragma once

#include "UserInterface/Components/MainPanel/Date.h"
#include "UserInterface/Components/MainPanel/Time.h"

class MainPanel {

	public:

		MainPanel() {
			_date = new Date();
			_time = new Time();
		}

		void render();
		void switchScreen(int vector);

	protected:

		const uint8_t COMPONENT_DATETIME = 1;
		const uint8_t COMPONENT_STOPWATCH = 2;

		const uint8_t COMPONENTS = 2;

		uint _currentComponent = COMPONENT_DATETIME;

		Date *_date;
		Time *_time;

		void _clear();

};
