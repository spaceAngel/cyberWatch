#include "config.h"

#include "ProgressBars.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainPanel/DateTime/SubComponents/ProgressBar.h"

void ProgressBars::render() {
	RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
	_bars[0]->render(currentTime.hour);
	_bars[1]->render(currentTime.minute);
	_bars[2]->render(currentTime.second);
}

ProgressBars::ProgressBars() {
	_bars[0] = new ProgressBar(10, 12, TFT_DARKGREEN);
	_bars[1] = new ProgressBar(55, 60, TFT_BLUE);
	_bars[2] = new ProgressBar(100, 60, TFT_DARKCYAN);
}

void ProgressBars::setShouldReRender(bool shouldReRender) {
	_bars[0]->setShouldReRender(shouldReRender);
	_bars[1]->setShouldReRender(shouldReRender);
	_bars[2]->setShouldReRender(shouldReRender);
}