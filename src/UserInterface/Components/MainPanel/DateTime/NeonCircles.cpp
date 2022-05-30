#include "config.h"

#include "NeonCircles.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainPanel/DateTime/SubComponents/NeonCircle.h"

NeonCircles::NeonCircles() {
	int32_t width = TTGOClass::getWatch()->tft->width() / 4;
	this->circles[0] = new NeonCircle(width, 50, 12, TFT_BLUE);
	this->circles[1] = new NeonCircle((width * 3), 50, 60, TFT_RED);
}

void NeonCircles::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	this->circles[0]->render(currentTime.hour);
	this->circles[1]->render(currentTime.minute);
	TTGOClass::getWatch()->tft->fillCircle(TTGOClass::getWatch()->tft->width() / 2, 68, 5, ((currentTime.second % 2) == 0) ? TFT_RED : TFT_BLUE);
	TTGOClass::getWatch()->tft->fillCircle(TTGOClass::getWatch()->tft->width() / 2, 88, 5, ((currentTime.second % 2) == 0) ? TFT_BLUE : TFT_RED);
}

void NeonCircles::setShouldReRender(bool shouldReRender) {
	this->circles[0]->setShouldReRender(shouldReRender);
	this->circles[1]->setShouldReRender(shouldReRender);
}