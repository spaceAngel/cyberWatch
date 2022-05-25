#include "config.h"

#include <LilyGoWatch.h>

#include "DateTime.h"
#include "UserInterface/Components/MainPanel/DateTime/Date.h"
#include "UserInterface/Components/MainPanel/DateTime/Time.h"
#include "UserInterface/Components/MainPanel/DateTime/AnalogClocks.h"

void DateTime::render() {
	if (_isDigital) {
		_date->render();
		_time->render();
	} else {
		_clocks->render();
	}
}

void DateTime::setShouldReRender(bool shouldReRender) {
	_date->setShouldReRender(shouldReRender);
	_time->setShouldReRender(shouldReRender);
	_clocks->setShouldReRender(shouldReRender);
}

bool DateTime::handleVerticalSwipe(int8_t vector) {
	_isDigital = !_isDigital;
	if (_isDigital) {
		_date->setShouldReRender(true);
		_time->setShouldReRender(true);
	} else {
		_clocks->setShouldReRender(true);
	}
	return true;
}

DateTime::DateTime() {
	_date = new Date();
	_time = new Time();
	_clocks = new AnalogClocks();
}

