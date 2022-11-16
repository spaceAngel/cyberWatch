#pragma once

#include "Apps/StopWatch.h"

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
