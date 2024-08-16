#include "config.h"

#include "LogoFace.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"
#include "Core/Hardware/RTC.h"
#include "UserInterface/BackgroundRenderer.h"

void LogoFace::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->shouldReRender() == true)
		|| currentTime.minute != this->prevMinute

	) {

		BackgroundRenderer::renderImage(BACKGROUND_LOGO, 0, 20);
		this->drawLine(
			((currentTime.hour % 12 ) * 5) + (currentTime.minute / 12),
			RADIUS-30,
			COLOR_MAIN_1
		);
		this->drawLine(currentTime.minute, RADIUS - 15, COLOR_MAIN_1);
		this->setShouldReRender(false);
		this->prevMinute = currentTime.minute;
	}
}

void LogoFace::drawLine(int32_t time, uint8_t radius, uint32_t color) {
	uint8_t x = TFT_WIDTH / 2;
	uint8_t y = 20 + TFT_HEIGHT / 2;

	int32_t x1 = Geometry::getCalculatedXPointOnCircle(x, (6 * time), radius);
	int32_t y1 = 20 + Geometry::getCalculatedYPointOnCircle(y, (6 * time), radius);

	for (int8_t i = -3; i <= 3; i++) {
		TTGOClass::getWatch()->tft->drawLine(x, y, x1 + i, y1 + i, color);
	}
}


