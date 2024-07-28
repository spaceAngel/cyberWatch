#include "config.h"

#include <LilyGoWatch.h>

#include "SensorGrid.h"
#include "Core/Hardware/RTC.h"
#include "Core/Hardware/Display.h"
#include "Utils/MathUtil.h"

void SensorGrid::render() {

	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->prevMinute != currentTime.minute)
		|| (this->shouldReRender())
	) {
		this->prevMinute = currentTime.minute;
		this->renderTime();
	}

	if (
		(this->prevSecond != currentTime.second)
		|| (this->shouldReRender())
	) {
		this->prevSecond = currentTime.second;
		this->renderSensorGrid();
	}
	this->setShouldReRender(false);
}

void SensorGrid::renderTime() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	char timeStr[6];
	(void)snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);
	TTGOClass::getWatch()->tft->setTextSize(2);
	TTGOClass::getWatch()->tft->fillRect(
		0,
		50,
		RESOLUTION_WIDTH,
		TTGOClass::getWatch()->tft->fontHeight() - 14,
		COLOR_BACKGROUND
	);

	TTGOClass::getWatch()->tft->drawString(
		timeStr,
		(RESOLUTION_WIDTH - TTGOClass::getWatch()->tft->textWidth(timeStr)) / 2,
		50
	);
	Display::getInstance()->resetTypographySettings();
}

void SensorGrid::renderSensorGrid() {
	TTGOClass::getWatch()->tft->fillRect(
		0, 0, RESOLUTION_WIDTH, 50, COLOR_BACKGROUND
	);
	for (uint8_t i = 0; i < this->getCellCount(); i++) {
		this->renderSensorGridCell(0);
	}

	TTGOClass::getWatch()->tft->fillRect(
		0, 95, RESOLUTION_WIDTH, 50, COLOR_BACKGROUND
	);
	for (uint8_t i = 0; i < this->getCellCount(); i++) {
		this->renderSensorGridCell(1);
	}
}

void SensorGrid::renderSensorGridCell(uint8_t line) {
	uint8_t color = MathUtil::getRandomUint8(3);
	TTGOClass::getWatch()->tft->fillRect(
		1 + MathUtil::getRandomUint8(11) * 24,
		MathUtil::getRandomUint8(2) * 12 + 6 + line * 95,
		22,
		11,
		this->colors[color]
	);
}

uint8_t SensorGrid::getCellCount() {
	return MathUtil::getRandomUint8(12) + 10;
}

SensorGrid::SensorGrid() {

}
