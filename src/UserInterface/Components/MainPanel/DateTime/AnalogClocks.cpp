#include "config.h"

#include "AnalogClocks.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

#include "UserInterface/Screens/MainScreen.h"

void AnalogClocks::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		this->shouldReRender()
		|| this->prevSecond != currentTime.second
	) {
		if (this->shouldReRender()) {
			this->renderFace();
		}
		this->clear();
		this->drawLine(
			(currentTime.hour % 12 ) * 5 + currentTime.minute / 12,
			36,
			TFT_DARKGREEN
		);
		this->drawLine(currentTime.minute, 52, TFT_DARKGREEN);
		this->drawLine(currentTime.second, 52, TFT_DARKGREY);
		this->prevSecond = currentTime.second;
		setShouldReRender(false);
	}
}

void AnalogClocks::drawLine(uint8_t time, uint8_t radius, uint32_t color) {
	int32_t x1, y1;
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

void AnalogClocks::clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		TTGOClass::getWatch()->tft->width() / 2,
		75,
		55,
		TFT_BLACK
	);
}

void AnalogClocks::renderFace() {
	for (uint8_t i = 1; i<= 60; i++) {
		int32_t x1, y1;
		Geometry::calculatePointOnCircle(
			TTGOClass::getWatch()->tft->width() / 2,
			75,
			6 * i,
			i % 5 == 0 ? 60 : 66,
			x1,
			y1
		);

		int32_t x2, y2;
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