#include "config.h"

#include "StopWatch.h"

#include <LilyGoWatch.h>

#include "System/AppsStatusMonitor.h"

void StopWatch::render() {
	long stopTime;
	if (this->running) {
		stopTime = millis() - this->startAt;
	} else {
		stopTime = this->stopAt - this->startAt;
	}
	if (
		stopTime != this->prevTime
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->setTextSize(2);
		if (this->shouldReRender()) {
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
		this->renderTime(stopTime > 0 ? stopTime : 0);
		TTGOClass::getWatch()->tft->setTextSize(1);
		this->prevTime = stopTime;
		this->setShouldReRender(false);
	}

}


bool StopWatch::handlePEKShort() {
	if (this->running) { //is running, PEK means stop
		this->running = false;
		this->stopAt = millis();
	} else {
		if (this->startAt == 0) { //no start value, start
			this->startAt = millis();
			this->running = true;
		} else { //reset
			this->startAt = 0;
			this->stopAt = 0;
		}
	}
	return false;
}

void StopWatch::renderTime(long stopTime) {
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
	this->renderHour(hours);
	this->renderMinutes(minutes);
	this->renderSeconds(seconds);
	this->renderMillis(stopTime);

}

bool StopWatch::isRunning() {
	return this->running;
}

void StopWatch::renderHour(uint8_t hours) {
	if (
		hours != this->prevHour
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(0, POS_Y, 28, 40, TFT_BLACK);
		char txt[3];
		snprintf(txt, sizeof(txt), "%01d", hours);
		TTGOClass::getWatch()->tft->drawString(txt, 3, POS_Y);
	}
}

void StopWatch::renderSeconds(uint8_t seconds) {
	if (
		seconds != this->prevSecond
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(113, POS_Y, 56, 40, TFT_BLACK);
		char txt[3];
		snprintf(txt, sizeof(txt), "%02d", seconds);
		TTGOClass::getWatch()->tft->drawString(txt, 113, POS_Y);
		this->prevSecond = seconds;
	}
}

void StopWatch::renderMinutes(uint8_t minutes) {
	if (
		minutes != this->prevMinute
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(42, POS_Y, 56, 40, TFT_BLACK);
		char txt[3];
		snprintf(txt, sizeof(txt), "%02d", minutes);
		TTGOClass::getWatch()->tft->drawString(txt, 42, POS_Y);
		this->prevMinute = minutes;
	}
}

void StopWatch::renderMillis(uint8_t millis) {
	TTGOClass::getWatch()->tft->fillRect(180, POS_Y, 56, 40, TFT_BLACK);
	char txt[3];
	snprintf(txt, sizeof(txt), "%02d", millis);
	TTGOClass::getWatch()->tft->drawString(txt, 180, POS_Y);

}

StopWatch::StopWatch() {
	AppsStatusMonitor::getInstance()->registerStopWatchComponent(this);
}


