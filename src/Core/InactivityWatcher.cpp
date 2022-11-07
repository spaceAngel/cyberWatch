#include "config.h"

#include "config.h"

#include "InactivityWatcher.h"
#include "Utils/TimeUtil.h"
#include "Core/Hardware/MoveSensor.h"
#include "Core/SystemTicker.h"

#include <LilyGoWatch.h>

InactivityWatcher* InactivityWatcher::inst;

InactivityWatcher *InactivityWatcher::getInstance() {
	if (InactivityWatcher::inst == nullptr) {
		InactivityWatcher::inst = new InactivityWatcher();
	}
	return InactivityWatcher::inst;
}

bool InactivityWatcher:: isInactive() {
	return (this->lastActivity + INACTIVITY_TRESHOLD) < TimeUtil::getCurrentTimeInSeconds();
}

void InactivityWatcher::markActivity() {
	this->lastActivity = TimeUtil::getCurrentTimeInSeconds();
	this->lastOnHandActivity = TimeUtil::getCurrentTimeInSeconds();
}

InactivityWatcher::InactivityWatcher() {
	this->lastActivity = TimeUtil::getCurrentTimeInSeconds();
	this->lastOnHandActivity = TimeUtil::getCurrentTimeInSeconds();
}

bool InactivityWatcher::isDetectedOnHand() {
	if (
		SystemTicker::getInstance()->isTickFor(TICKER_DETECT_ONHAND)
	) {
		Accel acc = MoveSensor::getInstance()->getAccel();
		bool sensorChanged = false;
		if (abs(acc.x) > DETECT_ONHAND_ACC_THRESHOLD) {
			this->lastOnHandActivity = TimeUtil::getCurrentTimeInSeconds();
			sensorChanged = true;
		}
		this->prevOnHandState = sensorChanged ||  ((this->lastOnHandActivity + INACTIVITY_ONHAMD_TRESHOLD) > TimeUtil::getCurrentTimeInSeconds());
	}
	return this->prevOnHandState;
}
