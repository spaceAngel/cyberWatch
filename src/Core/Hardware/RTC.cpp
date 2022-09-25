#include "config.h"

#include <LilyGoWatch.h>

#include "RTC.h"

#include "Core/SystemTicker.h"

RTC* RTC::inst;

RTC *RTC::getInstance() {
	if (RTC::inst == nullptr) {
		RTC::inst = new RTC();
	}
	return RTC::inst;
}

RTC_Date RTC::getCurrentDate() {
	if (
		SystemTicker::getInstance()->isTickFor(TICKER_DATETIME)
	) {
		this->lastDateTime = TTGOClass::getWatch()->rtc->getDateTime();
	}
	return this->lastDateTime;
}

RTC::RTC() {
	this->lastDateTime = TTGOClass::getWatch()->rtc->getDateTime();
}