#include "config.h"

#include "ProgressBars.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainPanel/DateTime/SubComponents/ProgressBar.h"

void ProgressBars::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	this->bars[0]->render(currentTime.hour);
	this->bars[1]->render(currentTime.minute);
	this->bars[2]->render(currentTime.second);
}

ProgressBars::ProgressBars() {
	this->bars[0] = new ProgressBar(10, 12, COLOR_MAIN_2);
	this->bars[1] = new ProgressBar(55, 60, COLOR_MAIN_1);
	this->bars[2] = new ProgressBar(100, 60, COLOR_MAIN_3);
}

void ProgressBars::setShouldReRender(bool shouldReRender) {
	this->bars[0]->setShouldReRender(shouldReRender);
	this->bars[1]->setShouldReRender(shouldReRender);
	this->bars[2]->setShouldReRender(shouldReRender);
}