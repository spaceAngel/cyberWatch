#include "config.h"

#include <LilyGoWatch.h>

#include "Time.h"
#include "Core/Hardware/RTC.h"

void Time::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->prevMinute != currentTime.minute)
		|| (this->shouldReRender())
	) {
		char timeStr[6];
		(void)snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);
		TTGOClass::getWatch()->tft->setTextSize(3);
		TTGOClass::getWatch()->tft->fillRect(
			0,
			POS_Y,
			TTGOClass::getWatch()->tft->width(),
			TTGOClass::getWatch()->tft->fontHeight() - 14,
			COLOR_BACKGROUND
		);

		TTGOClass::getWatch()->tft->drawString(
			timeStr,
			(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(timeStr)) / 2,
			POS_Y
		);
		TTGOClass::getWatch()->tft->setTextSize(1); // reset size to default
		this->prevMinute = currentTime.minute;
		setShouldReRender(false);
	}
}
