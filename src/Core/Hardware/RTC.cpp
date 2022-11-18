#include "config.h"

#include <LilyGoWatch.h>

#include "RTC.h"

#include "Core/SystemTicker.h"
#include "Events/EventManager.h"

RTC* RTC::inst;

RTC *RTC::getInstance() {
	if (RTC::inst == nullptr) {
		RTC::inst = new RTC();
	}
	return RTC::inst;
}

RTC_Date RTC::getCurrentDate() {
	this->updateDate();
	return this->lastDateTime;
}

void RTC::updateDate() {
	if (
		SystemTicker::getInstance()->isTickFor(TICKER_DATETIME)
	) {
		RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
		if (currentDate.second != this->lastDateTime.second) {
			this->lastDateTime = currentDate;
			EventManager::getInstance()->fireEvent(EVENT_TIME_CHANGE);
		}

	}
}

RTC::RTC() {
	this->lastDateTime = TTGOClass::getWatch()->rtc->getDateTime();
}