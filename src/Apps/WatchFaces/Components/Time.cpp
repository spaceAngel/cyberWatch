#include "config.h"

#include <LilyGoWatch.h>

#include "Time.h"
#include "Core/Hardware/RTC.h"
#include "Core/Hardware/Display.h"

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
			TFT_WIDTH,
			TTGOClass::getWatch()->tft->fontHeight() - 14,
			COLOR_BACKGROUND
		);

		TTGOClass::getWatch()->tft->drawString(
			timeStr,
			(TFT_WIDTH - TTGOClass::getWatch()->tft->textWidth(timeStr)) / 2,
			POS_Y
		);
		Display::getInstance()->resetTypographySettings();
		this->prevMinute = currentTime.minute;
		setShouldReRender(false);
	}
}
