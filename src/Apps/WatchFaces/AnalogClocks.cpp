#include "config.h"

#include "AnalogClocks.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

#include "UserInterface/Screens/MainScreen.h"
#include "Core/Hardware/RTC.h"
#include "Core/SystemTicker.h"
#include "Utils/DateUtil.h"

void AnalogClocks::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->shouldReRender() == true)
		|| currentTime.second != this->prevSecond

	) {
		if (this->shouldReRender() == true) {
			this->renderFace();
		}
		this->clear();
		this->drawLine(
			((currentTime.hour % 12 ) * 5) + (currentTime.minute / 12),
			RADIUS-30,
			COLOR_MAIN_1
		);
		this->drawLine(currentTime.minute, RADIUS - 15, COLOR_MAIN_1);
		this->drawLine(currentTime.second, RADIUS - 15, COLOR_MAIN_3);
		this->renderDate(currentTime);
		setShouldReRender(false);
		this->prevSecond = currentTime.second;
	}
}

void AnalogClocks::drawLine(int32_t time, uint8_t radius, uint32_t color) {
	uint8_t x = RESOLUTION_WIDTH / 2;
	uint8_t y = POS_Y;

	int32_t x1 = Geometry::getCalculatedXPointOnCircle(x, (6 * time), radius);
	int32_t y1 = Geometry::getCalculatedYPointOnCircle(y, (6 * time), radius);

	TTGOClass::getWatch()->tft->drawLine(x, y, x1, y1, color);
	TTGOClass::getWatch()->tft->drawLine(x, y, x1 + 1, y1 + 1, color);
	TTGOClass::getWatch()->tft->drawLine(x, y, x1 - 1, y1 - 1, color);
}

void AnalogClocks::clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		RESOLUTION_WIDTH / 2,
		POS_Y,
		RADIUS - 10,
		COLOR_BACKGROUND
	);
}

void AnalogClocks::renderFace() {
	for (int32_t i = 1; i <= 60; i++) {
		int32_t x1 = Geometry::getCalculatedXPointOnCircle(RESOLUTION_WIDTH / 2, 6 * i, ((i % 5) == 0) ? RADIUS - 5 : RADIUS);
		int32_t y1 = Geometry::getCalculatedYPointOnCircle(POS_Y, 6 * i, ((i % 5) == 0) ? RADIUS - 5 : RADIUS);

		int32_t x2 = Geometry::getCalculatedXPointOnCircle(RESOLUTION_WIDTH / 2, 6 * i, RADIUS);
		int32_t y2 = Geometry::getCalculatedYPointOnCircle(POS_Y, 6 * i, RADIUS);

		TTGOClass::getWatch()->tft->drawLine(x1, y1, x2, y2, COLOR_MAIN_1);
	}
}

void AnalogClocks::renderDate(RTC_Date date) {
	TTGOClass::getWatch()->tft->fillRect(
		(RESOLUTION_WIDTH - 100) / 2,
		POS_Y - 37,
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
		(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth(dateStr)) / 2,
		POS_Y - 36
	);
}
