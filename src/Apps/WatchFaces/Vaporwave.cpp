#include "config.h"

#include <LilyGoWatch.h>

#include "Vaporwave.h"
#include "Core/Hardware/RTC.h"
#include "Core/Hardware/Display.h"
#include "Utils/DateUtil.h"
#include "UserInterface/BackgroundRenderer.h"

void Vaporwave::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->prevMinute != currentTime.minute)
		|| (this->shouldReRender())
	) {
		this->prevMinute = currentTime.minute;
		BackgroundRenderer::renderImage(BACKGROUND_WATCH_VAPORWAVE);
		this->renderTime();
		this->renderDate();
		Display::getInstance()->resetTypographySettings();
		this->setShouldReRender(false);
	}
}


void Vaporwave::renderTime() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	char timeStr[6];
	(void)snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);
	TTGOClass::getWatch()->tft->setTextSize(1);
	TTGOClass::getWatch()->tft->setTextFont(7);
	TTGOClass::getWatch()->tft->setTextColor(TFT_BLACK);

	TTGOClass::getWatch()->tft->drawString(
		timeStr,
		50,
		46
	);
}

void Vaporwave::renderDate() {
	RTC_Date currentDate = RTC::getInstance()->getCurrentDate();
	char dateStr[8];
	TTGOClass::getWatch()->tft->setTextSize(4);
	TTGOClass::getWatch()->tft->setTextFont(1);
	TTGOClass::getWatch()->tft->setTextColor(TFT_BLACK);
	char dayInWeek[4];
	DateUtil::weekdayNameShort(dayInWeek, currentDate.year,currentDate.month, currentDate.day);
	(void)snprintf(dateStr, sizeof(dateStr), "%s%  02d",dayInWeek, currentDate.day);
	uint8_t dateStringWidth = TTGOClass::getWatch()->tft->textWidth(dateStr);
	TTGOClass::getWatch()->tft->drawString(
		dateStr,
		(RESOLUTION_WIDTH - dateStringWidth) / 2,
		110
	);


}