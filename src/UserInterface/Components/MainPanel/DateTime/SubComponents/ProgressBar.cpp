#include "config.h"

#include "ProgressBar.h"

#include <LilyGoWatch.h>

ProgressBar::ProgressBar(uint8_t y, uint8_t maxValue, long color) {
	_color = color;
	_maxValue = maxValue;
	_y = y;
}

void ProgressBar::render(uint8_t value) {
	if (
		shouldReRender()
		|| _prevValue != value
	) {
		TTGOClass::getWatch()->tft->fillRect(
			0,
			_y,
			TTGOClass::getWatch()->tft->width(),
			40,
			TFT_BLACK
		);
		char txt[3];
		snprintf(txt, sizeof(txt), "%02d", value);
		TTGOClass::getWatch()->tft->setTextColor(_color);
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->drawString(txt, 15, _y);
		TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
		TTGOClass::getWatch()->tft->setTextSize(1);
		TTGOClass::getWatch()->tft->fillCircle(BAR_START, _y + 20, BAR_HEIGHT / 2, _color);
		uint8_t width = TTGOClass::getWatch()->tft->width() - BAR_START - 20;
		TTGOClass::getWatch()->tft->fillRect(
			BAR_START + 2,
			_y + BAR_HEIGHT - 1,
			(width / _maxValue) * (value > _maxValue ? value % _maxValue : value),
			BAR_HEIGHT + 1,
			_color
		);
		TTGOClass::getWatch()->tft->fillCircle(
			BAR_START + (width / _maxValue) * (value > _maxValue ? value % _maxValue : value),
			_y + 20,
			BAR_HEIGHT / 2,
			_color
		);
		_prevValue = value;
		for (uint8_t i = 0; i< 6; i++) {
			TTGOClass::getWatch()->tft->fillRect(
				BAR_START + 2 + i * (width / 6),
				_y,
				2,
				35,
				TFT_BLACK
			);
		}
		setShouldReRender(false);
	}
}