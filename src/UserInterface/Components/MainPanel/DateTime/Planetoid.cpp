#include "config.h"

#include "Planetoid.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

#include "UserInterface/Screens/MainScreen.h"

void Planetoid::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	if (
		this->shouldReRender()
		|| (this->prevSecond != currentTime.second)
	) {
		this->clear();
		this->renderFace();
		this->renderPoint(6 * (((currentTime.hour % 12 ) * 5) + (currentTime.minute / 12)), 38, 5, TFT_RED);
		this->renderPoint(6 * currentTime.minute, 60, 5, TFT_RED);
		this->renderPoint(6 * currentTime.second, 30, 4, TFT_BLUE);
		this->prevSecond = currentTime.second;
		setShouldReRender(false);
	}
}

void Planetoid::clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		TTGOClass::getWatch()->tft->width() / 2,
		75,
		68,
		TFT_BLACK
	);
}

void Planetoid::renderFace() {
	for (int32_t i = 0; i < 60; i += 5) {
		this->renderPoint(6 * i, 48, 2, TFT_DARKGREEN);
	}
}

void Planetoid::renderPoint(uint16_t angle, uint8_t radius, uint8_t size, int color) {
	int32_t x1;
	int32_t y1;
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
