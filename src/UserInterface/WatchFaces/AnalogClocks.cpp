#include "config.h"

#include "AnalogClocks.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

#include "UserInterface/Screens/MainScreen.h"
#include "Core/Hardware/RTC.h"
#include "Core/SystemTicker.h"

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
			36,
			COLOR_MAIN_1
		);
		this->drawLine(currentTime.minute, 52, COLOR_MAIN_1);
		this->drawLine(currentTime.second, 52, COLOR_MAIN_3);
		setShouldReRender(false);
		this->prevSecond = currentTime.second;
	}
}

void AnalogClocks::drawLine(int32_t time, uint8_t radius, uint32_t color) {
	uint8_t x = TTGOClass::getWatch()->tft->width() / 2;
	uint8_t y = 75;

	int32_t x1 = Geometry::getCalculatedXPointOnCircle(x, (6 * time), radius);
	int32_t y1 = Geometry::getCalculatedYPointOnCircle(y, (6 * time), radius);

	if (y1 > 150) { y1 = 140;}
	TTGOClass::getWatch()->tft->drawLine(x, y, x1, y1, color);
	TTGOClass::getWatch()->tft->drawLine(x, y, x1 + 1, y1 + 1, color);
	TTGOClass::getWatch()->tft->drawLine(x, y, x1 - 1, y1 - 1, color);
}

void AnalogClocks::clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		TTGOClass::getWatch()->tft->width() / 2,
		75,
		55,
		COLOR_BACKGROUND
	);
}

void AnalogClocks::renderFace() {
	for (int32_t i = 1; i <= 60; i++) {
		int32_t x1 = Geometry::getCalculatedXPointOnCircle(TTGOClass::getWatch()->tft->width() / 2, 6 * i, ((i % 5) == 0) ? 60 : 66);
		int32_t y1 = Geometry::getCalculatedYPointOnCircle(75, 6 * i, ((i % 5) == 0) ? 60 : 66);

		int32_t x2 = Geometry::getCalculatedXPointOnCircle(TTGOClass::getWatch()->tft->width() / 2, 6 * i, 68);
		int32_t y2 = Geometry::getCalculatedYPointOnCircle(75, 6 * i, 68);

		TTGOClass::getWatch()->tft->drawLine(x1, y1, x2, y2, COLOR_MAIN_1);
	}
}