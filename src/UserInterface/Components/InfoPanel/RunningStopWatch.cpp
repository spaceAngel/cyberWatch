#include "config.h"

#include "RunningStopWatch.h"

#include <LilyGoWatch.h>

#include "System/AppsStatusMonitor.h"

void RunningStopWatch::render() {
	Serial.print("\n\n\nKarel\n\n");

	bool state = AppsStatusMonitor::getInstance()->isStopWatchRunning();
	if (state != _wasRunning) {
		if (state == false) {
			_clear();
		} else {
			_renderIcon();
		}
		this->_wasRunning = state;

	}

	Serial.print("\n\nahn\n\n");

}


void RunningStopWatch::_clear() {
	TTGOClass::getWatch()->tft->fillRect(
		POS_X - 3,
		POS_Y - 3,
		24,
		24,
		TFT_BLACK
	);
}

void RunningStopWatch::_renderIcon() {
	TTGOClass::getWatch()->tft->drawCircle(
		POS_X + 9,
		POS_Y + 9,
		10,
		TFT_DARKGREEN
	);

	TTGOClass::getWatch()->tft->drawCircle(
		POS_X + 9,
		POS_Y + 9,
		9,
		TFT_DARKGREEN
	);

	TTGOClass::getWatch()->tft->drawLine(
		POS_X + 9,
		POS_Y + 9,
		POS_X + 9,
		POS_Y,
		TFT_DARKGREEN
	);

	TTGOClass::getWatch()->tft->drawLine(
		POS_X + 9,
		POS_Y + 9,
		POS_X + 16,
		POS_Y + 4,
		TFT_DARKGREEN
	);

	TTGOClass::getWatch()->tft->fillRect(
		POS_X + 8,
		POS_Y - 3,
		4,
		4,
		TFT_DARKGREEN
	);
}