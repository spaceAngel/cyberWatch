#include "config.h"

#include "Planetoid.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

#include "UserInterface/Screens/MainScreen.h"

void Planetoid::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		shouldReRender()
		|| _prevSecond != currentTime.second
	) {
		_clear();
		_renderFace();
		_renderPoint(6 * ((currentTime.hour % 12 ) * 5 + currentTime.minute / 12), 38, 5, TFT_RED);
		_renderPoint(6 * currentTime.minute, 60, 5, TFT_RED);
		_renderPoint(6 * currentTime.second, 30, 4, TFT_BLUE);
		_prevSecond = currentTime.second;
		setShouldReRender(false);
	}
}

void Planetoid::_clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		TTGOClass::getWatch()->tft->width() / 2,
		75,
		68,
		TFT_BLACK
	);
}

void Planetoid::_renderFace() {
	for (uint8_t i = 0; i < 60; i += 5) {
		_renderPoint(6 * i, 48, 2, TFT_DARKGREEN);
	}
}

void Planetoid::_renderPoint(uint16_t angle, uint8_t radius, uint8_t size, int color) {
	uint8_t x1, y1;
	uint8_t x = TTGOClass::getWatch()->tft->width() / 2;
	uint8_t y = 75;
	Geometry::calculatePointOnCircle(
		x,
		y,
		angle,
		radius,
		x1,
		y1
	);
	TTGOClass::getWatch()->tft->fillCircle(x1, y1, size, color);
}
