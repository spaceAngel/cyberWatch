#include "config.h"

#include "ProgressBar.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"

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
			RESOLUTION_WIDTH,
			40,
			COLOR_BACKGROUND
		);
		char txt[3];
		(void)snprintf(txt, sizeof(txt), "%02d", value);
		TTGOClass::getWatch()->tft->setTextColor(this->color);
		TTGOClass::getWatch()->tft->setTextSize(2);
		TTGOClass::getWatch()->tft->drawString(txt, 15, this->y);
		Display::getInstance()->resetTypographySettings();
		int32_t width = RESOLUTION_WIDTH - BAR_START - 10;
		TTGOClass::getWatch()->tft->fillRoundRect(
			BAR_START,
			this->y + 10,
			10 + (width / this->maxValue) * ((value > this->maxValue) ? (value % this->maxValue) : value),
			BAR_HEIGHT,
			10,
			this->color
		);

		this->prevValue = value;
		for (int32_t i = 0; i< 6; i++) {
			TTGOClass::getWatch()->tft->fillRect(
				BAR_START + 2 + (i * (width / 6)),
				this->y,
				2,
				35,
				COLOR_BACKGROUND
			);
		}
		setShouldReRender(false);
	}
}