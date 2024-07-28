#include "config.h"

#include "NeonCircle.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"
#include "Core/Hardware/Esp32.h"
#include "Core/Hardware/Display.h"

NeonCircle::NeonCircle(uint8_t x, uint8_t y, uint8_t maxValue, long color) {
	this->x = x;
	this->y = y;
	this->color = color;
	this->maxValue = maxValue;
}

void NeonCircle::render(int32_t value) {
	if (
		(this->prevValue != value)
		|| this->shouldReRender()
	) {

		Esp32::getInstance()->runWithCpuSpeedHigh(
			[value, this]() {
				this->renderCircle(value);
			}
		);
		this->setShouldReRender(false);
		this->prevValue = value;
	}
}

void NeonCircle::renderCircle(int32_t value) {
	TTGOClass::getWatch()->tft->setTextColor(this->color);
	TTGOClass::getWatch()->tft->setTextSize(2);
	TTGOClass::getWatch()->tft->fillCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 44, this->color);
	TTGOClass::getWatch()->tft->fillCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 34, COLOR_BACKGROUND);
	TTGOClass::getWatch()->tft->drawCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 49, this->color);
	TTGOClass::getWatch()->tft->drawCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 50, this->color);
	int32_t step = 360 / this->maxValue;
	for (int32_t i = 0; i < 12; i++) {
		TTGOClass::getWatch()->tft->fillTriangle(
			this->x,
			this->y + TTGOClass::getWatch()->tft->fontHeight() / 2,
			Geometry::getCalculatedXPointOnCircle(this->x, (i * 30) + 3, 44),
			Geometry::getCalculatedYPointOnCircle(this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, (i * 30) + 2, 44),
			Geometry::getCalculatedXPointOnCircle(this->x, (i * 30) - 2, 44),
			Geometry::getCalculatedYPointOnCircle(this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, (i * 30) - 3, 44),
			TFT_BLACK
		);

	}
	for (int32_t i = ((value < this->maxValue) ? value : (value % this->maxValue)) * step; i < (this->maxValue * step); i++) {
		int32_t pointX = Geometry::getCalculatedXPointOnCircle(this->x, i, 45 );
		int32_t pointY = Geometry::getCalculatedYPointOnCircle(this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, i, 45);

		TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY, COLOR_BACKGROUND);
		TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY+1, COLOR_BACKGROUND);
		TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY-1, COLOR_BACKGROUND);
	}

	char txt[3];
	(void)snprintf(txt, sizeof(txt), "%02d", value);
	TTGOClass::getWatch()->tft->drawString(
		txt,
		this->x - TTGOClass::getWatch()->tft->textWidth(txt) / 2,
		this->y + 6
	);

	Display::getInstance()->resetTypographySettings();
}
