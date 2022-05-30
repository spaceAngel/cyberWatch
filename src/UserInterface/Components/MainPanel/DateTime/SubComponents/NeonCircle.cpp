#include "config.h"

#include "NeonCircle.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

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
		TTGOClass::getWatch()->tft->setTextColor(this->color);
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->fillCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 44, this->color);
		TTGOClass::getWatch()->tft->fillCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 34, TFT_BLACK);
		TTGOClass::getWatch()->tft->drawCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 49, this->color);
		TTGOClass::getWatch()->tft->drawCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, 50, this->color);
		int32_t step = 360 / this->maxValue;
		for (int32_t i = 0; i < 12; i++) {
			int32_t pointX;
			int32_t pointY;
			Geometry::calculatePointOnCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, (i * 30), 44, pointX, pointY);
			TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY, TFT_BLACK);
			Geometry::calculatePointOnCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, (i * 30) + 1, 44, pointX, pointY);
			TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY, TFT_BLACK);
		}
		for (int32_t i = ((value < this->maxValue) ? value : (value % this->maxValue)) * step; i < (this->maxValue * step); i++) {
			int32_t pointX;
			int32_t pointY;
			Geometry::calculatePointOnCircle(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, i, 44, pointX, pointY);
			TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY, TFT_BLACK);
			TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY+1, TFT_BLACK);
			TTGOClass::getWatch()->tft->drawLine(this->x, this->y + TTGOClass::getWatch()->tft->fontHeight() / 2, pointX, pointY-1, TFT_BLACK);
		}
		char txt[3];
		(void)snprintf(txt, sizeof(txt), "%02d", value);
		TTGOClass::getWatch()->tft->drawString(
			txt,
			this->x - TTGOClass::getWatch()->tft->textWidth(txt) / 2,
			this->y + 6
		);

		TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
		TTGOClass::getWatch()->tft->setTextSize(1);
		setShouldReRender(false);
		this->prevValue = value;
	}
}
