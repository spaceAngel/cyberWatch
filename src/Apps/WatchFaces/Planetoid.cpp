#include "config.h"

#include "Planetoid.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

#include "Core/SystemTicker.h"
#include "Core/Hardware/RTC.h"

void Planetoid::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		this->shouldReRender()
		|| currentTime.second != this->prevSecond
	) {
		this->clear();
		this->renderFace();
		this->renderPoint(6 * (((currentTime.hour % 12 ) * 5) + (currentTime.minute / 12)), RADIUS - 20,  5, COLOR_MAIN_1);
		this->renderPoint(6 * currentTime.minute, RADIUS , 5, COLOR_MAIN_2);
		this->renderPoint(6 * currentTime.second, RADIUS - 30, 4, COLOR_MAIN_3);
		setShouldReRender(false);
		this->prevSecond = currentTime.second;
	}
}

void Planetoid::clear() {
	TTGOClass::getWatch()->tft->fillCircle(
		RESOLUTION_WIDTH / 2,
		POS_Y,
		RADIUS + 10,
		COLOR_BACKGROUND
	);
}

void Planetoid::renderFace() {
	for (int32_t i = 0; i < 60; i += 5) {
		this->renderPoint(6 * i, RADIUS - 10, 2, COLOR_MAIN_1);
	}
}

void Planetoid::renderPoint(uint16_t angle, uint8_t radius, uint8_t size, int color) {
	uint8_t x = RESOLUTION_WIDTH / 2;
	uint8_t y = POS_Y;
	int32_t calculatedX = Geometry::getCalculatedXPointOnCircle(x, angle, radius);
	int32_t calculatedY = Geometry::getCalculatedYPointOnCircle(y, angle, radius);
	TTGOClass::getWatch()->tft->fillCircle(
		calculatedX,
		calculatedY,
		(int32_t)size,
		color
	);
}
