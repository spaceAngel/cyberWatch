#include "config.h"

#include "RunningStopWatch.h"

#include <LilyGoWatch.h>

#include "Core/AppsStatusMonitor.h"
#include "UserInterface/Icons/StopWatch.h"
#include "UserInterface/UserInterfaceManager.h"

void RunningStopWatch::render() {
	bool state = AppsStatusMonitor::getInstance()->isStopWatchRunning();
	if (state != this->wasRunning) {
		if (state == false) {
			this->clear();
		} else {
			UserInterfaceManager::getInstance()->renderIcon(iconStopWatch, POS_X, POS_Y);
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
