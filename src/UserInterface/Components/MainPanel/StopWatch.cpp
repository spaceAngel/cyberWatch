#include "config.h"

#include "StopWatch.h"

#include <LilyGoWatch.h>

#include "System/AppsStatusMonitor.h"

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
		TTGOClass::getWatch()->tft->setTextSize(2);
		if (shouldReRender()) {
			TTGOClass::getWatch()->tft->fillRect(
				0,
				POS_Y,
				TTGOClass::getWatch()->tft->width(),
				70,
				TFT_BLACK
			);
			TTGOClass::getWatch()->tft->drawString(
				"0:00:00.00",
				0,
				POS_Y
			);
		}
		_renderTime(stopTime > 0 ? stopTime : 0);
		TTGOClass::getWatch()->tft->setTextSize(1);
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
	return false;
}

void StopWatch::_renderTime(long stopTime) {
	uint8_t hours = 0;
	uint8_t minutes = 0;
	uint8_t seconds = 0;
	hours = stopTime / 3600000;
	stopTime = stopTime  - hours * 3600000;
	minutes = stopTime / 60000;
	stopTime = stopTime - minutes * 60000;
	seconds = stopTime / 1000;
	stopTime = stopTime - seconds * 1000;
	stopTime = stopTime / 10;

	char txt[12];
	//snprintf(
	//	txt,
	//	sizeof(txt),
	//	"%d:%02d:%02d.%02d",
	//	hours, minutes, seconds, stopTime
	//);
	_renderHour(hours);
	_renderMinutes(minutes);
	_renderSeconds(seconds);
	_renderMillis(stopTime);

}

bool StopWatch::isRunning() {
	return _isRunning;
}

void StopWatch::_renderHour(uint8_t hours) {
	if (
		hours != _prevHour
		|| shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(0, POS_Y, 28, 40, TFT_BLACK);
		char txt[3];
		snprintf(txt, sizeof(txt), "%01d", hours);
		TTGOClass::getWatch()->tft->drawString(txt, 3, POS_Y);
	}
}

void StopWatch::_renderSeconds(uint8_t seconds) {
	if (
		seconds != _prevSecond
		|| shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(113, POS_Y, 56, 40, TFT_BLACK);
		char txt[3];
		snprintf(txt, sizeof(txt), "%02d", seconds);
		TTGOClass::getWatch()->tft->drawString(txt, 113, POS_Y);
		_prevSecond = seconds;
	}
}

void StopWatch::_renderMinutes(uint8_t minutes) {
	if (
		minutes != _prevMinute
		|| shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(42, POS_Y, 56, 40, TFT_BLACK);
		char txt[3];
		snprintf(txt, sizeof(txt), "%02d", minutes);
		TTGOClass::getWatch()->tft->drawString(txt, 42, POS_Y);
		_prevMinute = minutes;
	}
}

void StopWatch::_renderMillis(uint8_t millis) {
	TTGOClass::getWatch()->tft->fillRect(180, POS_Y, 56, 40, TFT_BLACK);
	char txt[3];
	snprintf(txt, sizeof(txt), "%02d", millis);
	TTGOClass::getWatch()->tft->drawString(txt, 180, POS_Y);

}

StopWatch::StopWatch() {
	AppsStatusMonitor::getInstance()->registerStopWatchComponent(this);
}


