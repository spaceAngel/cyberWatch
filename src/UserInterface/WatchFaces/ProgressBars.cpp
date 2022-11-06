#include "config.h"

#include "ProgressBars.h"

#include <LilyGoWatch.h>

#include "UserInterface/WatchFaces/Components/ProgressBar.h"
#include "Core/SystemTicker.h"
#include "Core/Hardware/RTC.h"

void ProgressBars::render() {
	if (
		SystemTicker::getInstance()->isTickFor(TICKER_CLOCKS)
		|| this->shouldReRender()
	) {
		RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
		this->bars[0]->render(currentTime.hour);
		this->bars[1]->render(currentTime.minute);
		this->bars[2]->render(currentTime.second);
	}
}

ProgressBars::ProgressBars() {
	this->bars[0] = new ProgressBar(10, 12, COLOR_MAIN_2);
	this->bars[1] = new ProgressBar(55, 60, COLOR_MAIN_1);
	this->bars[2] = new ProgressBar(100, 60, COLOR_MAIN_3);
}

void ProgressBars::setShouldReRender(bool shouldReRender) {
	Component::setShouldReRender(shouldReRender);
	this->bars[0]->setShouldReRender(shouldReRender);
	this->bars[1]->setShouldReRender(shouldReRender);
	this->bars[2]->setShouldReRender(shouldReRender);
}