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
		(stopTime != this->prevTime)
		|| this->shouldReRender() == true
	) {
		TTGOClass::getWatch()->tft->setTextSize(2);
		if (this->shouldReRender() == true) {
			TTGOClass::getWatch()->tft->fillRect(
				0,
				POS_Y,
				TTGOClass::getWatch()->tft->width(),
				70,
				COLOR_BACKGROUND
			);
			TTGOClass::getWatch()->tft->drawString(":",	30, POS_Y - 3);
			TTGOClass::getWatch()->tft->drawString(":",	99, POS_Y - 3);
			TTGOClass::getWatch()->tft->drawString(".",	168, POS_Y);
		}
		this->renderTime((stopTime > 0) ? stopTime : 0);
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

void StopWatch::renderTime(int64_t stopTime) {
	int64_t stopTimeMs = stopTime;
	int64_t hours = 0;
	int64_t minutes = 0;
	int64_t seconds = 0;
	hours = stopTimeMs / 3600000;
	stopTimeMs = stopTimeMs - (hours * 3600000);
	minutes = stopTimeMs / 60000;
	stopTimeMs = stopTimeMs - (minutes * 60000);
	seconds = stopTimeMs / 1000;
	stopTimeMs = stopTimeMs - (seconds * 1000);
	stopTimeMs = stopTimeMs / 10;

	this->renderHour(hours);
	this->renderMinutes(minutes);
	this->renderSeconds(seconds);
	this->renderMillis(stopTimeMs);
}

bool StopWatch::isRunning() {
	return this->running;
}

void StopWatch::renderHour(uint8_t hours) {
	if (
		(hours != this->prevHour)
		|| this->shouldReRender() == true
	) {
		TTGOClass::getWatch()->tft->fillRect(0, POS_Y, 28, 40, COLOR_BACKGROUND);
		char txt[3];
		(void)snprintf(txt, sizeof(txt), "%01d", hours);
		TTGOClass::getWatch()->tft->drawString(txt, 3, POS_Y);
	}
}

void StopWatch::renderSeconds(uint8_t seconds) {
	if (
		(seconds != this->prevSecond)
		|| this->shouldReRender() == true
	) {
		TTGOClass::getWatch()->tft->fillRect(113, POS_Y, 56, 40, COLOR_BACKGROUND);
		char txt[3];
		(void)snprintf(txt, sizeof(txt), "%02d", seconds);
		TTGOClass::getWatch()->tft->drawString(txt, 113, POS_Y);
		this->prevSecond = seconds;
	}
}

void StopWatch::renderMinutes(uint8_t minutes) {
	if (
		(minutes != this->prevMinute)
		|| this->shouldReRender() == true
	) {
		TTGOClass::getWatch()->tft->fillRect(42, POS_Y, 56, 40, COLOR_BACKGROUND);
		char txt[3];
		(void)snprintf(txt, sizeof(txt), "%02d", minutes);
		TTGOClass::getWatch()->tft->drawString(txt, 42, POS_Y);
		this->prevMinute = minutes;
	}
}

void StopWatch::renderMillis(uint8_t millis) {
	TTGOClass::getWatch()->tft->fillRect(180, POS_Y, 56, 40, COLOR_BACKGROUND);
	char txt[3];
	(void)snprintf(txt, sizeof(txt), "%02d", millis);
	TTGOClass::getWatch()->tft->drawString(txt, 180, POS_Y);
}

StopWatch::StopWatch() {
	AppsStatusMonitor::getInstance()->registerStopWatchComponent(this);
}


bool StopWatch::isSystemSleepForbidden() {
	return this->getIsActive();
}
