#include "config.h"

#include "NeonCircles.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainPanel/WatchFaces/SubComponents/NeonCircle.h"

NeonCircles::NeonCircles() {
	int32_t width = TTGOClass::getWatch()->tft->width() / 4;
	this->circles[0] = new NeonCircle(width, 50, 12, COLOR_MAIN_2);
	this->circles[1] = new NeonCircle((width * 3), 50, 60, COLOR_MAIN_1);
}

void NeonCircles::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	this->circles[0]->render(currentTime.hour);
	this->circles[1]->render(currentTime.minute);
	TTGOClass::getWatch()->tft->fillCircle(TTGOClass::getWatch()->tft->width() / 2, 68, 5, ((currentTime.second % 2) == 0) ? COLOR_MAIN_2 : COLOR_MAIN_1);
	TTGOClass::getWatch()->tft->fillCircle(TTGOClass::getWatch()->tft->width() / 2, 88, 5, ((currentTime.second % 2) == 0) ? COLOR_MAIN_1 : COLOR_MAIN_2);
}

void NeonCircles::setShouldReRender(bool shouldReRender) {
	this->circles[0]->setShouldReRender(shouldReRender);
	this->circles[1]->setShouldReRender(shouldReRender);
}