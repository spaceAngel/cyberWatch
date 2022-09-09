#include "config.h"

#include "InactivityWatcher.h"

#include "Utils/TimeUtil.h"

InactivityWatcher* InactivityWatcher::inst;

InactivityWatcher *InactivityWatcher::getInstance() {
	if (InactivityWatcher::inst == nullptr) {
		InactivityWatcher::inst = new InactivityWatcher();
	}
	return InactivityWatcher::inst;
}

bool InactivityWatcher::isInactive() {
	return (this->lastActivity + INACTIVITY_TRESHOLD) < TimeUtil::getCurrentTimeInSeconds();
}

void InactivityWatcher::markActivity() {
	this->lastActivity = TimeUtil::getCurrentTimeInSeconds();
}

InactivityWatcher::InactivityWatcher() {
	this->lastActivity = TimeUtil::getCurrentTimeInSeconds();
}
