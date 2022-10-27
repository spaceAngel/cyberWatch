#include "config.h"

#include <LilyGoWatch.h>

#include "SensorGrid.h"
#include "Core/Hardware/RTC.h"

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
		TTGOClass::getWatch()->tft->width(),
		TTGOClass::getWatch()->tft->fontHeight() - 14,
		COLOR_BACKGROUND
	);

	TTGOClass::getWatch()->tft->drawString(
		timeStr,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(timeStr)) / 2,
		50
	);
	TTGOClass::getWatch()->tft->setTextSize(1); // reset size to default
}

void SensorGrid::renderSensorGrid() {
	TTGOClass::getWatch()->tft->fillRect(
		0, 0, TTGOClass::getWatch()->tft->width(), 50, COLOR_BACKGROUND
	);
	for (uint8_t i = 0; i < this->getCellCount(); i++) {
		this->renderSensorGridCell(0);
	}

	TTGOClass::getWatch()->tft->fillRect(
		0, 95, TTGOClass::getWatch()->tft->width(), 50, COLOR_BACKGROUND
	);
	for (uint8_t i = 0; i < this->getCellCount(); i++) {
		this->renderSensorGridCell(1);
	}
}

void SensorGrid::renderSensorGridCell(uint8_t line) {
	uint8_t col;
	uint8_t row;
	uint8_t color;

	while( ( col = rand() ) > 11 )  {}
	while( ( row = rand() ) > 2 )  {}
	while( ( color = rand() ) > 3 )  {}

	TTGOClass::getWatch()->tft->fillRect(
		1 + col * 24,
		row * 12 + 6 + line * 95,
		22,
		11,
		this->colors[color]
	);
}

uint8_t SensorGrid::getCellCount() {
	uint8_t cells;
	while( ( cells = rand() ) > 12)  {}
	return cells + 10;
}

SensorGrid::SensorGrid() {

}
