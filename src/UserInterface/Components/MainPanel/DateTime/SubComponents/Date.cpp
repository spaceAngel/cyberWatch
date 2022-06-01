#include "config.h"

#include <LilyGoWatch.h>

#include "Date.h"
#include "Utils/DateUtil.h"

void Date::render() {
	RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		(this->prevDay != currentDate.day)
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(
			0,
			POS_Y,
			TTGOClass::getWatch()->tft->width(),
			(TTGOClass::getWatch()->tft->fontHeight() - 1) * 2,
			COLOR_BACKGROUND
		);

		this->renderDate(currentDate);
		this->renderDayInWeek(currentDate);
		this->prevDay = currentDate.day;
		setShouldReRender(false);
	}
}

void Date::renderDate(RTC_Date currentDate) {
	char dateStr[11];
	(void)snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%02d", currentDate.day, currentDate.month, currentDate.year);
	TTGOClass::getWatch()->tft->drawString(
		dateStr,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(dateStr)) / 2,
		POS_Y + 2 +(TTGOClass::getWatch()->tft->fontHeight())
	);
}

void Date::renderDayInWeek(RTC_Date currentDate) {
	char dayInWeek[10];
	this->weekday(dayInWeek, currentDate.year,currentDate.month, currentDate.day);
	TTGOClass::getWatch()->tft->drawString(
		dayInWeek,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(dayInWeek)) / 2,
		POS_Y + 3
	);
}

// calculation of weekday used from here https://forum.arduino.cc/t/rtc-clock-with-days-of-week/426045/4
void Date::weekday(char *dayInWeekStr, uint year, uint8_t month, uint8_t day) {
	uint8_t dayInWeek = DateUtil::weekday(year, month, day);
	switch (dayInWeek) {
		case 0: (void)strcpy(dayInWeekStr, "Sunday"); break;
		case 1: (void)strcpy(dayInWeekStr, "Monday"); break;
		case 2: (void)strcpy(dayInWeekStr, "Tuesday"); break;
		case 3: (void)strcpy(dayInWeekStr, "Wednesday"); break;
		case 4: (void)strcpy(dayInWeekStr, "Thursday"); break;
		case 5: (void)strcpy(dayInWeekStr, "Friday"); break;
		case 6: (void)strcpy(dayInWeekStr, "Saturday"); break;
	}
}
