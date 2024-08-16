#include "config.h"

#include "AnalogClocks.h"

#include <LilyGoWatch.h>

#include "Utils/Geometry.h"
#include "Core/Hardware/RTC.h"
#include "Utils/DateUtil.h"
#include "UserInterface/BackgroundRenderer.h"

void AnalogClocks::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->shouldReRender() == true)
		|| currentTime.minute != this->prevMinute

	) {
		if (this->shouldReRender() == true) {
			BackgroundRenderer::renderImage(BACKGROUND_WATCH_ANALOG);
		}
		this->clear();
		this->drawLine(
			((currentTime.hour % 12 ) * 5) + (currentTime.minute / 12),
			RADIUS-30,
			COLOR_MAIN_1
		);
		this->drawLine(currentTime.minute, RADIUS - 15, COLOR_MAIN_1);
		this->renderDate(currentTime);
		this->setShouldReRender(false);
		this->prevMinute = currentTime.minute;
	}
}

void AnalogClocks::drawLine(int32_t time, uint8_t radius, uint32_t color) {
	uint8_t x = TFT_WIDTH / 2;
	uint8_t y = TFT_HEIGHT / 2;

	int32_t x1 = Geometry::getCalculatedXPointOnCircle(x, (6 * time), radius);
	int32_t y1 = Geometry::getCalculatedYPointOnCircle(y, (6 * time), radius);

	for (int8_t i = -3; i <= 3; i++) {
		TTGOClass::getWatch()->tft->drawLine(x, y, x1 + i, y1 + i, color);
	}

}

void AnalogClocks::clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		TFT_WIDTH / 2,
		TFT_HEIGHT / 2,
		RADIUS - 10,
		COLOR_BACKGROUND
	);
}

void AnalogClocks::renderDate(RTC_Date date) {
	TTGOClass::getWatch()->tft->fillRect(
		(TFT_WIDTH - 100) / 2,
		TFT_HEIGHT / 2 - 50,
		100,
		24,
		COLOR_BACKGROUND
	);
	char dateStr[11];
	char dayInWeek[2];

	DateUtil::weekdayNameShort(dayInWeek, date.year, date.month, date.day);
	(void)snprintf(dateStr, sizeof(dateStr), "%s %02d/%02d", dayInWeek, date.day, date.month);
	TTGOClass::getWatch()->tft->drawString(
		dateStr,
		(TFT_WIDTH - TTGOClass::getWatch()->tft->textWidth(dateStr)) / 2,
		TFT_HEIGHT / 2 - 50
	);
}
