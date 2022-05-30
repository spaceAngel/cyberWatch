#include "config.h"

#include "ProgressBar.h"

#include <LilyGoWatch.h>

ProgressBar::ProgressBar(uint8_t y, uint8_t maxValue, long color) {
	this->color = color;
	this->maxValue = maxValue;
	this->y = y;
}

void ProgressBar::render(int32_t value) {
	if (
		this->shouldReRender()
		|| (this->prevValue != value)
	) {
		TTGOClass::getWatch()->tft->fillRect(
			0,
			this->y,
			TTGOClass::getWatch()->tft->width(),
			40,
			TFT_BLACK
		);
		char txt[3];
		snprintf(txt, sizeof(txt), "%02d", value);
		TTGOClass::getWatch()->tft->setTextColor(this->color);
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->drawString(txt, 15, this->y);
		TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
		TTGOClass::getWatch()->tft->setTextSize(1);
		TTGOClass::getWatch()->tft->fillCircle(BAR_START, this->y + 20, BAR_HEIGHT / 2, this->color);
		int32_t width = TTGOClass::getWatch()->tft->width() - BAR_START - 20;
		TTGOClass::getWatch()->tft->fillRect(
			BAR_START + 2,
			this->y + BAR_HEIGHT - 1,
			(width / this->maxValue) * ((value > this->maxValue) ? (value % this->maxValue) : value),
			BAR_HEIGHT + 1,
			this->color
		);
		TTGOClass::getWatch()->tft->fillCircle(
			BAR_START + (width / this->maxValue) * ((value > this->maxValue) ? (value % this->maxValue) : value),
			this->y + 20,
			BAR_HEIGHT / 2,
			this->color
		);
		this->prevValue = value;
		for (int32_t i = 0; i< 6; i++) {
			TTGOClass::getWatch()->tft->fillRect(
				BAR_START + 2 + (i * (width / 6)),
				this->y,
				2,
				35,
				TFT_BLACK
			);
		}
		setShouldReRender(false);
	}
}