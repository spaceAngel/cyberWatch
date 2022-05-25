#include "config.h"

#include "AnalogClocks.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

#include "UserInterface/Screens/MainScreen.h"

void AnalogClocks::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		shouldReRender()
		|| _prevSecond != currentTime.second
	) {
		if (shouldReRender()) {
			_renderFace();
		}
		_clear();
		_drawLine(
			(currentTime.hour % 12 ) * 5 + currentTime.minute / 12,
			36,
			TFT_DARKGREEN
		);
		_drawLine(currentTime.minute, 52, TFT_DARKGREEN);
		_drawLine(currentTime.second, 52, TFT_DARKGREY);
		_prevSecond = currentTime.second;
		setShouldReRender(false);
	}
}

void AnalogClocks::_drawLine(uint8_t time, uint8_t radius, uint32_t color) {
	uint8_t x1, y1;
	uint8_t x = TTGOClass::getWatch()->tft->width() / 2;
	uint8_t y = 75;
	Geometry::calculatePointOnCircle(
		x,
		y,
		6 * time,
		radius,
		x1,
		y1
	);

	if (y1 > 150) { y1 = 140;}
	TTGOClass::getWatch()->tft->drawLine(x, y, x1, y1, color);
	TTGOClass::getWatch()->tft->drawLine(x, y, x1 + 1, y1 + 1, color);
	TTGOClass::getWatch()->tft->drawLine(x, y, x1 - 1, y1 - 1, color);
}

void AnalogClocks::_clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		TTGOClass::getWatch()->tft->width() / 2,
		75,
		55,
		TFT_BLACK
	);
}

void AnalogClocks::_renderFace() {
	for (uint8_t i = 1; i<= 60; i++) {
		uint8_t x1, y1;
		Geometry::calculatePointOnCircle(
			TTGOClass::getWatch()->tft->width() / 2,
			75,
			6 * i,
			i % 5 == 0 ? 60 : 66,
			x1,
			y1
		);

		uint8_t x2, y2;
		Geometry::calculatePointOnCircle(
			TTGOClass::getWatch()->tft->width() / 2,
			75,
			6 * i,
			68,
			x2,
			y2
		);
		TTGOClass::getWatch()->tft->drawLine(x1, y1, x2, y2, TFT_DARKGREEN);

	}
}