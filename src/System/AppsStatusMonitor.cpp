#include "config.h"

#include "AppsStatusMonitor.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainPanel/StopWatch.h"


AppsStatusMonitor* AppsStatusMonitor::_inst;

AppsStatusMonitor *AppsStatusMonitor::getInstance() {

	if (AppsStatusMonitor::_inst == nullptr) {
		AppsStatusMonitor::_inst = new AppsStatusMonitor();
	}
	return AppsStatusMonitor::_inst;
}

void AppsStatusMonitor::registerStopWatchComponent(StopWatch *stopWatch) {
	_stopWatch = stopWatch;
}

bool AppsStatusMonitor::isStopWatchRunning() {
	return _stopWatch->isRunning();
}