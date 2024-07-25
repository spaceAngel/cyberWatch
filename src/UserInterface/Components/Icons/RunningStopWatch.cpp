#include "config.h"

#include "RunningStopWatch.h"

#include <LilyGoWatch.h>

#include "Apps/StopWatch/StopWatchRegistry.h"
#include "UserInterface/Icons/StopWatch.h"
#include "UserInterface/UserInterfaceManager.h"

void RunningStopWatch::render() {
	bool state = StopWatchRegistry::getInstance()->getRunning();
	if (
		state != this->wasRunning
		|| this->shouldReRender()
	) {
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
