#include "config.h"

#include <LilyGoWatch.h>

#include "Calendar.h"
#include "UserInterface/Components/MainPanel.h"
#include "Utils/DateUtil.h"
#include "Core/Hardware/Esp32.h"

Calendar::Calendar() {
	RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
	year = currentDate.year;
	month = currentDate.month;
	day = currentDate.day;
}

void Calendar::render() {
	if (this->shouldReRender() == true) {

		Esp32::getInstance()->runWithCpuSpeedHigh(
			[this] {

				uint8_t dayInWeek = DateUtil::weekday(this->year, this->month, 1);
				uint8_t day = 0;
				uint8_t row = 0;
				while (day < DateUtil::getDaysInMonth(this->year, this->month)) {

					if ((int32_t)dayInWeek == 0) {
						dayInWeek = 7;
					}
					day++;
					this->renderDay(day, row, dayInWeek);
					this->renderIsNowBox(day, row, dayInWeek);
					this->renderDelimiter(day, row, dayInWeek);
					if (((int32_t)dayInWeek % 7) == 0) {
						dayInWeek = 0;
						row++;
					}
					dayInWeek++;
				}
			}
		);
		this->renderMonthYearLabel();
		this->setShouldReRender(false);
	}
}

void Calendar::renderDelimiter(uint8_t day, uint8_t row, uint8_t dayInWeek) {
	if (
		((int32_t)dayInWeek < 7)
		&& ((int32_t)day < DateUtil::getDaysInMonth(this->year, this->month))
	) {
		TTGOClass::getWatch()->tft->drawLine(
			(int32_t)dayInWeek * 34,
			(2 + ((int32_t)row * 23)),
			((int32_t)dayInWeek * 34),
			2 + (((int32_t)row + 1) * 23),
			COLOR_MAIN_1
		);
	}
}

void Calendar::renderIsNowBox(uint8_t day, uint8_t row, uint8_t dayInWeek) {
	RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		(this->year == currentDate.year)
		&& (this->month == currentDate.month)
		&& (day == currentDate.day)
	) {
		TTGOClass::getWatch()->tft->drawRect(
			(1 + ((int32_t)dayInWeek - 1) * 34),
			(4 + ((int32_t)row * 23)),
			33,
			24,
			COLOR_MAIN_2
		);
	}
}

void Calendar::renderDay(uint8_t day, uint8_t row, uint8_t dayInWeek) {
	char str[4];
	(void)snprintf(str, sizeof(str), "%d", day);

	TTGOClass::getWatch()->tft->drawString(
		str,
		(((int32_t)day < 10) ? 13 : 0) + 3 + (((int32_t)dayInWeek - 1) * 34),
		(6 + ((int32_t)row * 23))
	);
}

void Calendar::renderMonthYearLabel() {
	char monthNameShort[4];
	DateUtil::monthNameShort(monthNameShort, this->month);
	TTGOClass::getWatch()->tft->drawString(monthNameShort, 182, 125);
	char year[5];
	(void)snprintf(year, sizeof(year), "%d", this->year);
	TTGOClass::getWatch()->tft->drawString(year, 120, 125);

}

void Calendar::prevMonth() {
	this->month--;
	if ((int32_t)this->month == 0) {
		this->month = 12;
		this->year--;
	}
	setShouldReRender(true);
}

void Calendar::nextMonth() {
	this->month++;
	if ((int32_t)this->month == 13) {
		this->month = 1;
		this->year++;
	}
	setShouldReRender(true);
}

bool Calendar::handleSwipeVertical(int8_t vector) {
	if (vector == -1) {
		this->nextMonth();
	} else {
		this->prevMonth();
	}
	this->setShouldReRender(true);
	return true;
}

bool Calendar::handlePEKShort() {
	RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
	this->year = currentDate.year;
	this->month = currentDate.month;
	this->setShouldReRender(true);
	return true;
}
