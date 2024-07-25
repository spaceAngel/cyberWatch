#include "config.h"

#include "AppsStatusMonitor.h"

#include <LilyGoWatch.h>

#include "Apps/StopWatch.h"

AppsStatusMonitor* AppsStatusMonitor::inst;

AppsStatusMonitor *AppsStatusMonitor::getInstance() {

	if (AppsStatusMonitor::inst == nullptr) {
		AppsStatusMonitor::inst = new AppsStatusMonitor();
	}
	return AppsStatusMonitor::inst;
}
