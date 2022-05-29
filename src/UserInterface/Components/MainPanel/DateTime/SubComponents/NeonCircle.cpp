#include "config.h"

#include "NeonCircle.h"

#include <LilyGoWatch.h>
#include "Utils/Geometry.h"

NeonCircle::NeonCircle(uint8_t x, uint8_t y, uint8_t maxValue, long color) {
	_x = x;
	_y = y;
	_color = color;
	_maxValue = maxValue;
}

void NeonCircle::render(uint8_t value) {
	if (
		_prevValue != value
		|| shouldReRender()
	) {
		TTGOClass::getWatch()->tft->setTextColor(_color);
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->fillCircle(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, 44, _color);
		TTGOClass::getWatch()->tft->fillCircle(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, 34, TFT_BLACK);
		TTGOClass::getWatch()->tft->drawCircle(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, 49, _color);
		TTGOClass::getWatch()->tft->drawCircle(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, 50, _color);
		uint8_t step = 360 / _maxValue;
		for (uint8_t i = 0; i < 12; i++) {
			uint8_t x, y;
			Geometry::calculatePointOnCircle(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, i * 30, 44, x, y);
			TTGOClass::getWatch()->tft->drawLine(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, x, y, TFT_BLACK);
			Geometry::calculatePointOnCircle(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, i * 30 + 1, 44, x, y);
			TTGOClass::getWatch()->tft->drawLine(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, x, y, TFT_BLACK);
		}
		for (uint16_t i = (value < _maxValue ? value : value % _maxValue) * step; i < _maxValue * step; i++) {
			uint8_t x, y;
			Geometry::calculatePointOnCircle(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, i, 44, x, y);
			TTGOClass::getWatch()->tft->drawLine(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, x, y, TFT_BLACK);
			TTGOClass::getWatch()->tft->drawLine(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, x, y+1, TFT_BLACK);
			TTGOClass::getWatch()->tft->drawLine(_x, _y + TTGOClass::getWatch()->tft->fontHeight() / 2, x, y-1, TFT_BLACK);
		}
		char txt[3];
		snprintf(txt, sizeof(txt), "%02d", value);
		TTGOClass::getWatch()->tft->drawString(
			txt,
			_x - TTGOClass::getWatch()->tft->textWidth(txt) / 2,
			_y + 6
		);

		TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
		TTGOClass::getWatch()->tft->setTextSize(1);
		setShouldReRender(false);
		_prevValue = value;
	}
}
