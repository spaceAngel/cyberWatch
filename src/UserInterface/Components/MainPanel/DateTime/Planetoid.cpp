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
		this->renderPoint(6 * (((currentTime.hour % 12 ) * 5) + (currentTime.minute / 12)), 38, 5, COLOR_WARN);
		this->renderPoint(6 * currentTime.minute, 60, 5, COLOR_WARN);
		this->renderPoint(6 * currentTime.second, 30, 4, COLOR_MAIN_1);
		this->prevSecond = currentTime.second;
		setShouldReRender(false);
	}
}

void Planetoid::clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		TTGOClass::getWatch()->tft->width() / 2,
		75,
		68,
		COLOR_BACKGROUND
	);
}

void Planetoid::renderFace() {
	for (int32_t i = 0; i < 60; i += 5) {
		this->renderPoint(6 * i, 48, 2, COLOR_MAIN_1);
	}
}

void Planetoid::renderPoint(uint16_t angle, uint8_t radius, uint8_t size, int color) {
	uint8_t x = TTGOClass::getWatch()->tft->width() / 2;
	uint8_t y = 75;

	TTGOClass::getWatch()->tft->fillCircle(
		Geometry::getCalculatedXPointOnCircle(x, angle, radius),
		Geometry::getCalculatedYPointOnCircle(y, angle, radius),
		(int32_t)size,
		color
	);
}
