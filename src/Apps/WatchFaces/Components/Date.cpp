#include "config.h"

#include <LilyGoWatch.h>

#include "Date.h"
#include "Utils/DateUtil.h"
#include "Core/Hardware/RTC.h"

void Date::render() {
	RTC_Date currentDate = RTC::getInstance()->getCurrentDate();
	if (
		(this->prevDay != currentDate.day)
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(
			0,
			POS_Y,
			RESOLUTION_WIDTH,
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
		(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth(dateStr)) / 2,
		POS_Y + 2 +(TTGOClass::getWatch()->tft->fontHeight())
	);
}

void Date::renderDayInWeek(RTC_Date currentDate) {
	char dayInWeek[10];
	DateUtil::weekdayName(dayInWeek, currentDate.year,currentDate.month, currentDate.day);
	TTGOClass::getWatch()->tft->drawString(
		dayInWeek,
		(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth(dayInWeek)) / 2,
		POS_Y + 3
	);
}


