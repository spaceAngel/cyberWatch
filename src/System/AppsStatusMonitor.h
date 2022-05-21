#pragma once

#include "UserInterface/Components/MainPanel/StopWatch.h"

class AppsStatusMonitor {

	public:

		static AppsStatusMonitor *getInstance();

		bool isStopWatchRunning();

		void registerStopWatchComponent(StopWatch *stopWatch);

	protected:

		static AppsStatusMonitor *_inst;

		StopWatch *_stopWatch;

		AppsStatusMonitor() {

		}

};