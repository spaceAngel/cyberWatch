#include "config.h"

#include "StopWatch.h"

#include <LilyGoWatch.h>

void StopWatch::render() {
	long stopTime;
	if (_isRunning) {
		stopTime = millis() - _startAt;
	} else {
		stopTime = _stopAt - _startAt;
	}
	if (
		stopTime != _prevTime
		|| shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(
			0,
			POS_Y,
			TTGOClass::getWatch()->tft->width(),
			70,
			TFT_BLACK
		);
		_renderTime(stopTime > 0 ? stopTime : 0);
		_prevTime = stopTime;
		setShouldReRender(false);
	}

}


bool StopWatch::handlePEKShort() {
	if (_isRunning) { //is running, PEK means stop
		_isRunning = false;
		_stopAt = millis();
	} else {
		if (_startAt == 0) { //no start value, start
			_startAt = millis();
			_isRunning = true;
		} else { //reset
			_startAt = 0;
			_stopAt = 0;
		}
	}
	return true;
}

void StopWatch::_renderTime(long stopTime) {
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
	hours = stopTime / 3600000;
	stopTime = stopTime  - hours * 3600000;
	minutes = stopTime / 60000;
	stopTime = stopTime - minutes * 6000;
	seconds = stopTime / 1000;
	stopTime = stopTime - seconds * 1000;
	stopTime = stopTime / 10;

	char txt[12];
	snprintf(
		txt,
		sizeof(txt),
		"%d:%02d:%02d.%02d",
		hours, minutes, seconds, stopTime
	);
	TTGOClass::getWatch()->tft->setTextSize(2);
	TTGOClass::getWatch()->tft->drawString(
		txt,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(txt)) / 2,
		POS_Y
	);
	TTGOClass::getWatch()->tft->setTextSize(1); // reset size to default



}