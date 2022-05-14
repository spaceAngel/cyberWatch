#include "config.h"

#include <LilyGoWatch.h>

#include "Date.h"

void Date::render() {
	RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		_prevDay != currentDate.day
	) {
		TTGOClass::getWatch()->tft->fillRect(
			0,
			POS_Y,
			TTGOClass::getWatch()->tft->width(),
			(TTGOClass::getWatch()->tft->fontHeight() - 1) * 2,
			TFT_BLACK
		);

		_renderDate(currentDate);
		_renderDayInWeek(currentDate);
		_prevDay = currentDate.day;
	}
}

void Date::_renderDate(RTC_Date currentDate) {
	char dateStr[11];
	snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%02d", currentDate.day, currentDate.month, currentDate.year);
	TTGOClass::getWatch()->tft->drawString(
		dateStr,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(dateStr)) / 2,
		POS_Y + 2 +(TTGOClass::getWatch()->tft->fontHeight())
	);
}

void Date::_renderDayInWeek(RTC_Date currentDate) {
	char dayInWeek[10];
	_weekday(dayInWeek, currentDate.year,currentDate.month, currentDate.day);
	TTGOClass::getWatch()->tft->drawString(
		dayInWeek,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(dayInWeek)) / 2,
		POS_Y + 3
	);
}

// calculation of weekday used from here https://forum.arduino.cc/t/rtc-clock-with-days-of-week/426045/4
void Date::_weekday(char *dayInWeekStr, int year, int month, int day) {
	int adjustment, mm, yy;
	if (year<2000) year+=2000;
	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;
	uint8_t dayInWeek = (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
	switch (dayInWeek) {
		case 0: strcpy(dayInWeekStr, "Sunday"); break;
		case 1: strcpy(dayInWeekStr, "Monday"); break;
		case 2: strcpy(dayInWeekStr, "Tuesday"); break;
		case 3: strcpy(dayInWeekStr, "Wednesday"); break;
		case 4: strcpy(dayInWeekStr, "Thursday"); break;
		case 5: strcpy(dayInWeekStr, "Friday"); break;
		case 6: strcpy(dayInWeekStr, "Saturday"); break;
	}
}
