#pragma once

#include "Apps/StopWatch.h"

class AppsStatusMonitor {

	public:

		static AppsStatusMonitor *getInstance();

	protected:

		static AppsStatusMonitor *inst;

		AppsStatusMonitor() {

		}

};
