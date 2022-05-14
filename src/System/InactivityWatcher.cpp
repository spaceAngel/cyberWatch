#include "config.h"

#include "InactivityWatcher.h"

#include "Utils/TimeUtil.h"

InactivityWatcher* InactivityWatcher::_inst;

InactivityWatcher *InactivityWatcher::getInstance() {
	if (InactivityWatcher::_inst == nullptr) {
		InactivityWatcher::_inst = new InactivityWatcher();
	}
	return InactivityWatcher::_inst;
}

bool InactivityWatcher::isInactive() {
	return _lastActivity + INACTIVITY_TRESHOLD < TimeUtil::getCurrentTimeInSeconds();
}

void InactivityWatcher::markActivity() {
	_lastActivity = TimeUtil::getCurrentTimeInSeconds();
}

InactivityWatcher::InactivityWatcher() {
	_lastActivity = TimeUtil::getCurrentTimeInSeconds();
}
