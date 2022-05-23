#pragma once

#include "UserInterface/Components/MainPanel/DateTime.h"
#include "UserInterface/Components/MainPanel/Calendar.h"
#include "UserInterface/Components/MainPanel/StopWatch.h"

class MainPanel {

	public:

		MainPanel() {
			_dateTime = new DateTime();
			_calendar = new Calendar();
			_stopWatch = new StopWatch();
		}

		void render();
		void switchScreen(int vector);
		void handleSwipeVertical(int vector);
		void handlePEKShort();
		bool isSleepForbidden();

	protected:

		const uint8_t COMPONENT_DATETIME = 1;
		const uint8_t COMPONENT_STOPWATCH = 2;
		const uint8_t COMPONENT_CALENDAR = 3;

		const uint8_t COMPONENTS = 3;

		uint _currentComponent = COMPONENT_DATETIME;

		DateTime *_dateTime;
		Calendar *_calendar;
		StopWatch *_stopWatch;

		void _clear();

};
