#include "config.h"

#include <LilyGoWatch.h>

#include "Lcars.h"
#include "Core/Hardware/RTC.h"
#include "Core/Hardware/Display.h"
#include "Images/LcarsBackground.h"
#include "Utils/DateUtil.h"


void Lcars::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->prevMinute != currentTime.minute)
		|| this->shouldReRender()
	) {
		this->prevMinute = currentTime.minute;
		if (this->shouldReRender()) {
			TTGOClass::getWatch()->tft->setSwapBytes(true);
			TTGOClass::getWatch()->tft->pushImage(0, 0, 240, 240, LcarsBackground.data);
		} else {
			TTGOClass::getWatch()->tft->fillRect(62, 37, 120, 100, TFT_BLACK);
		}
		TTGOClass::getWatch()->tft->setTextFont(4);
		this->renderTime();
		this->renderDate();
		this->steps->setShouldReRender(true);
	}
	this->battery->render();
	this->watchState->render();
	this->steps->render();
	Display::getInstance()->resetTypographySettings();
	this->setShouldReRender(false);
}

void Lcars::renderDate() {
	RTC_Date currentDate = RTC::getInstance()->getCurrentDate();
	char dateStr[8];
	TTGOClass::getWatch()->tft->setTextSize(1);
	TTGOClass::getWatch()->tft->setTextColor(TFT_VIOLET);
	char dayInWeek[4];
	DateUtil::weekdayNameShort(dayInWeek, currentDate.year,currentDate.month, currentDate.day);
	(void)snprintf(dateStr, sizeof(dateStr), "%s%  02d",dayInWeek, currentDate.day);
	TTGOClass::getWatch()->tft->drawString(
		dateStr,
		62,
		37
	);
}

void Lcars::renderTime() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	char timeStr[6];
	(void)snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);
	TTGOClass::getWatch()->tft->setTextSize(2);
	TTGOClass::getWatch()->tft->setTextColor(TFT_ORANGE);
	TTGOClass::getWatch()->tft->drawString(
		timeStr,
		57,
		87
	);
}