#include "config.h"

#include "RunningStopWatch.h"

#include <LilyGoWatch.h>

#include "System/AppsStatusMonitor.h"

void RunningStopWatch::render() {
	Serial.print("\n\n\nKarel\n\n");

	bool state = AppsStatusMonitor::getInstance()->isStopWatchRunning();
	if (state != this->wasRunning) {
		if (state == false) {
			this->clear();
		} else {
			this->renderIcon();
		}
		this->wasRunning = state;

	}

	Serial.print("\n\nahn\n\n");

}


void RunningStopWatch::clear() {
	TTGOClass::getWatch()->tft->fillRect(
		(int32_t)POS_X - 3,
		(int32_t)POS_Y - 3,
		24,
		24,
		COLOR_BACKGROUND
	);
}

void RunningStopWatch::renderIcon() {
	TTGOClass::getWatch()->tft->drawCircle(
		(int32_t)POS_X + 9,
		(int32_t)POS_Y + 9,
		10,
		COLOR_MAIN_1
	);

	TTGOClass::getWatch()->tft->drawCircle(
		(int32_t)POS_X + 9,
		(int32_t)POS_Y + 9,
		9,
		COLOR_MAIN_1
	);

	TTGOClass::getWatch()->tft->drawLine(
		(int32_t)POS_X + 9,
		(int32_t)POS_Y + 9,
		(int32_t)POS_X + 9,
		(int32_t)POS_Y,
		COLOR_MAIN_1
	);

	TTGOClass::getWatch()->tft->drawLine(
		(int32_t)POS_X + 9,
		(int32_t)POS_Y + 9,
		(int32_t)POS_X + 16,
		(int32_t)POS_Y + 4,
		COLOR_MAIN_1
	);

	TTGOClass::getWatch()->tft->fillRect(
		(int32_t)POS_X + 8,
		(int32_t)POS_Y - 3,
		4,
		4,
		COLOR_MAIN_1
	);
}