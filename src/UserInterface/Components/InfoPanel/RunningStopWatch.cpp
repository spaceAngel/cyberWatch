#include "config.h"

#include "RunningStopWatch.h"

#include <LilyGoWatch.h>

#include "System/AppsStatusMonitor.h"
#include "UserInterface/Icons/StopWatch.h"

void RunningStopWatch::render() {
	bool state = AppsStatusMonitor::getInstance()->isStopWatchRunning();
	if (state != this->wasRunning) {
		if (state == false) {
			this->clear();
		} else {
			TTGOClass::getWatch()->tft->setSwapBytes(true);
			TTGOClass::getWatch()->tft->pushImage(POS_X, POS_Y, 22, 22, iconStopWatch);
		}
		this->wasRunning = state;
	}
}

void RunningStopWatch::clear() {
	TTGOClass::getWatch()->tft->fillRect(
		(int32_t)POS_X,
		(int32_t)POS_Y,
		23,
		23,
		COLOR_BACKGROUND
	);
}
