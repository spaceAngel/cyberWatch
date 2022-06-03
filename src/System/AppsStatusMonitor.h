#pragma once

#include "UserInterface/Components/MainPanel/StopWatch.h"
#include "UserInterface/Components/MainPanel/DateTime.h"

class AppsStatusMonitor {

	public:

		static AppsStatusMonitor *getInstance();

		bool isStopWatchRunning();

		void registerStopWatchComponent(StopWatch *stopWatch);

		void registerDateTimeComponent(DateTime *dateTime);

		bool isDateTimeAlwaysOn();

	protected:

		static AppsStatusMonitor *inst;

		StopWatch *stopWatch;

		DateTime *dateTime;

		AppsStatusMonitor() {

		}

};