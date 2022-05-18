#include "config.h"

#include <LilyGoWatch.h>

#include "Calendar.h"
#include "UserInterface/Components/MainPanel.h"
#include "Utils/DateUtil.h"

Calendar::Calendar() {
	RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
	_year = currentDate.year;
	_month = currentDate.month;
	_day = currentDate.day;
}

void Calendar::render() {
	if (shouldReRender()) {
		uint8_t dayInWeek = DateUtil::weekday(_year, _month, 1);
		uint8_t day = 0;
		uint8_t row = 0;
		while (day < DateUtil::getDaysInMonth(_year, _month)) {

			if (dayInWeek == 0) {
				dayInWeek = 7;
			}
			day++;
			_renderDay(day, row, dayInWeek);
			_renderIsNowBox(day, row, dayInWeek);
			_renderDelimiter(day, row, dayInWeek);
			if (dayInWeek % 7 == 0) {
				dayInWeek = 0;
				row++;
			}
			dayInWeek++;
		}
		_renderMonthYearLabel();
		setShouldReRender(false);
	}
}

void Calendar::_renderDelimiter(uint8_t day, uint8_t row, uint8_t dayInWeek) {
	if (
		dayInWeek < 7
		&& day < DateUtil::getDaysInMonth(_year, _month)
	) {
		TTGOClass::getWatch()->tft->drawLine(
			dayInWeek * 34,
			2 + row * 23,
			dayInWeek * 34,
			2 + (row + 1) * 23,
			TFT_DARKGREEN
		);
	}
}

void Calendar::_renderIsNowBox(uint8_t day, uint8_t row, uint8_t dayInWeek) {
	RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		_year == currentDate.year
		&& _month == currentDate.month
		&& day == currentDate.day
	) {
		TTGOClass::getWatch()->tft->drawRect(
			1 + (dayInWeek - 1) * 34,
			4 + row * 23,
			33,
			24,
			TFT_RED
		);
	}
}

void Calendar::_renderDay(uint8_t day, uint8_t row, uint8_t dayInWeek) {
	char str[4];
	snprintf(str, sizeof(str), "%d", day);

	TTGOClass::getWatch()->tft->drawString(
		str,
		(day < 10 ? 13 : 0) + 3 + (dayInWeek - 1) * 34,
		6 + row * 23
	);
}

void Calendar::_renderMonthYearLabel() {
	char month[3];
	DateUtil::monthNameShort(month, _month);
	TTGOClass::getWatch()->tft->drawString(month, 182, 125);
	char year[5];
	snprintf(year, sizeof(year), "%d", _year);
	TTGOClass::getWatch()->tft->drawString(year, 120, 125);

}

void Calendar::prevMonth() {
	_month--;
	if (_month == 0) {
		_month = 12;
		_year--;
	}
	setShouldReRender(true);
}

void Calendar::nextMonth() {
	_month++;
	if (_month == 13) {
		_month = 1;
		_year++;
	}
	setShouldReRender(true);
}

bool Calendar::handleVerticalSwipe(int8_t vector) {
	if (vector == -1) {
		nextMonth();
	} else {
		prevMonth();
	}
	setShouldReRender(true);
	return true;
}