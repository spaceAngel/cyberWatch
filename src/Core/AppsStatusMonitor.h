#pragma once

#include "UserInterface/Apps/StopWatch.h"

class AppsStatusMonitor {

	public:

		static AppsStatusMonitor *getInstance();

		bool isStopWatchRunning();

		void registerStopWatchComponent(StopWatch *stopWatch);

	protected:

		static AppsStatusMonitor *inst;

		StopWatch *stopWatch;

		AppsStatusMonitor() {

		}

};
