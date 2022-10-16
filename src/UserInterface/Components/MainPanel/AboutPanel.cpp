#include "config.h"

#include "AboutPanel.h"

#include <LilyGoWatch.h>
#include "Environment/compilationdata.h"
#include "Environment/SystemInfo.h"

void AboutPanel::render() {

	uint uptime = SystemInfo::getInstance()->getUptime();
	if (this->prevUptime < uptime) {
		this->renderCompilationData();

		TTGOClass::getWatch()->tft->drawString("Up:",  10, this->calculatePosY(2, true));

		TTGOClass::getWatch()->tft->fillRect(
			75,
			this->calculatePosY(2, true) - 10,
			TTGOClass::getWatch()->tft->width(),
			TTGOClass::getWatch()->tft->fontHeight() * 2.4,
			COLOR_BACKGROUND
		);
		this->renderDateDiff(uptime, 2);
		TTGOClass::getWatch()->tft->drawString("Unpl:",  10, this->calculatePosY(3, true));
		if (SystemInfo::getInstance()->getPluggedIn() == false) {
			this->renderDateDiff(SystemInfo::getInstance()->getUnplugTime(), 3);
		} else {
			TTGOClass::getWatch()->tft->drawString(
			"plugged",
			TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth("plugged") - 15,
			this->calculatePosY(3, true)
	);
		}
	}
	this->prevUptime = uptime;
}

void AboutPanel::renderDateDiff(uint seconds, uint8_t row) {
	char str[20];
	this->secondsToString(seconds, str);
	TTGOClass::getWatch()->tft->drawString(
		str,
		TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(str) - 15,
		this->calculatePosY(row, true)
	);
}

void AboutPanel::renderCompilationData() {
	TTGOClass::getWatch()->tft->drawString(
		APP_VERSION,
		(TTGOClass::getWatch()->tft->width() / 4) - (TTGOClass::getWatch()->tft->textWidth(APP_VERSION) / 2),
		this->calculatePosY(0, false)
	);
	TTGOClass::getWatch()->tft->drawString(
		compilationCommit,
		(TTGOClass::getWatch()->tft->width() / 2) - 10,
		this->calculatePosY(0, false)
	);
	TTGOClass::getWatch()->tft->drawString(
		compilationDate,
		(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(compilationDate)) / 2,
		this->calculatePosY(1, false)
	);
}

uint8_t AboutPanel::calculatePosY(uint8_t row, bool shifted) {
	return (shifted ? 30 : 15)
	+ (TTGOClass::getWatch()->tft->fontHeight() * (row * 1.1));
}

void AboutPanel::secondsToString(uint totalSeconds, char (&string)[20]) {

	uint hours = 0;
	uint minutes = 0;
	uint days = 0;
	days = totalSeconds / (24 * 60 * 60);
	totalSeconds -= days * (24 * 60 * 60);
	hours = totalSeconds / (60 * 60);
	totalSeconds -= hours * (60 * 60);
	minutes = totalSeconds / 60;
	totalSeconds -= minutes * 60;
	if (days > 0) {
		snprintf(string, sizeof(string), "%d d  %02d:%02d:%02d",  days, hours, minutes, totalSeconds);
	} else {
		snprintf(string, sizeof(string), " %02d:%02d:%02d", hours, minutes, totalSeconds);
	}
}

AboutPanel::AboutPanel() {

}

