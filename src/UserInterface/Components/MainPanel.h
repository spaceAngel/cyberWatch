#pragma once

#include "UserInterface/Components/MainPanel/DateTime.h"
#include "UserInterface/Components/MainPanel/Calendar.h"
#include "UserInterface/Components/MainPanel/StopWatch.h"
#include "UserInterface/Components/MainComponent.h"

class MainPanel {

	public:

		MainPanel() {
			this->dateTime = new DateTime();
			this->calendar = new Calendar();
			this->stopWatch = new StopWatch();
		}

		void render();
		void switchScreen(int vector);
		void handleSwipeVertical(int vector);
		void handlePEKShort();
		bool isSleepForbidden();
		MainComponent *getCurrentComponent();

	protected:

		const uint8_t COMPONENT_DATETIME = 1;
		const uint8_t COMPONENT_STOPWATCH = 2;
		const uint8_t COMPONENT_CALENDAR = 3;

		const uint8_t COMPONENTS = 3;

		uint currentComponent = COMPONENT_DATETIME;

		DateTime *dateTime;
		Calendar *calendar;
		StopWatch *stopWatch;

		void clear();

};
