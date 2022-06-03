#include "config.h"

#include "AppsStatusMonitor.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainPanel/StopWatch.h"


AppsStatusMonitor* AppsStatusMonitor::inst;

AppsStatusMonitor *AppsStatusMonitor::getInstance() {

	if (AppsStatusMonitor::inst == nullptr) {
		AppsStatusMonitor::inst = new AppsStatusMonitor();
	}
	return AppsStatusMonitor::inst;
}

void AppsStatusMonitor::registerStopWatchComponent(StopWatch *stopWatch) {
	this->stopWatch = stopWatch;
}

void AppsStatusMonitor::registerDateTimeComponent(DateTime *dateTime) {
	this->dateTime = dateTime;
}

bool AppsStatusMonitor::isStopWatchRunning() {
	return this->stopWatch->isRunning();
}

bool AppsStatusMonitor::isDateTimeAlwaysOn() {
	return this->dateTime->isSystemSleepForbidden();
}