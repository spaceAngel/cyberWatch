#include "config.h"

#include <LilyGoWatch.h>

#include "Mosaic.h"
#include "Core/Hardware/RTC.h"
#include "Core/Hardware/Display.h"
#include "Utils/DateUtil.h"
#include "Utils/MathUtil.h"

void Mosaic::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->prevMinute != currentTime.minute)
		|| (this->shouldReRender())
	) {
		this->prevMinute = currentTime.minute;
		this->renderBackground();
		TTGOClass::getWatch()->tft->setTextColor(TFT_BLACK);
		this->renderTime();
		this->renderDate();
		Display::getInstance()->resetTypographySettings();
		this->setShouldReRender(false);
	}
}

void Mosaic::renderBackground() {
	uint8_t bg = MathUtil::getRandomUint8(Mosaic::COLORS_COUNT);
	TTGOClass::getWatch()->tft->fillScreen(
		this->colors[bg]
	);
	for (uint16_t i = 0; i < MathUtil::getRandomUint8(Mosaic::PARTS) + Mosaic::PARTS_MIN; i++) {
		uint8_t x = MathUtil::getRandomUint8(180);
		uint8_t y = MathUtil::getRandomUint8(180);
		uint8_t w = MathUtil::getRandomUint8(80);
		uint8_t h = MathUtil::getRandomUint8(80);
		uint8_t c = 200;
		while (c == 200 || c == bg) {
			c = MathUtil::getRandomUint8(Mosaic::COLORS_COUNT);
		}

		TTGOClass::getWatch()->tft->fillRoundRect(
			x, y, w, h, 10, this->colors[c]
		);
	}
}

void Mosaic::renderTime() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	char timeStr[6];
	(void)snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);
	TTGOClass::getWatch()->tft->setTextSize(9);
	TTGOClass::getWatch()->tft->setTextFont(1);

	TTGOClass::getWatch()->tft->drawString(
		timeStr,
		(TFT_WIDTH - TTGOClass::getWatch()->tft->textWidth(timeStr)) / 2,
		46
	);
}

void Mosaic::renderDate() {
	RTC_Date currentDate = RTC::getInstance()->getCurrentDate();
	char dateStr[8];
	TTGOClass::getWatch()->tft->setTextSize(6);
	TTGOClass::getWatch()->tft->setTextFont(1);
	char dayInWeek[4];
	DateUtil::weekdayNameShort(dayInWeek, currentDate.year,currentDate.month, currentDate.day);
	(void)snprintf(dateStr, sizeof(dateStr), "%s%  02d",dayInWeek, currentDate.day);
	TTGOClass::getWatch()->tft->drawString(
		dateStr,
		(TFT_WIDTH - TTGOClass::getWatch()->tft->textWidth(dateStr)) / 2,
		150
	);


}