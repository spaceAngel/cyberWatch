#include "config.h"

#include <LilyGoWatch.h>

#include "DateTime.h"
#include "UserInterface/Components/MainPanel/DateTime/DigitalClocks.h"
#include "UserInterface/Components/MainPanel/DateTime/AnalogClocks.h"

void DateTime::render() {
	if (_isDigital) {
		_digital->render();
	} else {
		_clocks->render();
	}
}

void DateTime::setShouldReRender(bool shouldReRender) {
	_digital->setShouldReRender(shouldReRender);
	_clocks->setShouldReRender(shouldReRender);
}

bool DateTime::handleVerticalSwipe(int8_t vector) {
	_isDigital = !_isDigital;
	if (_isDigital) {
		_digital->setShouldReRender(true);
	} else {
		_clocks->setShouldReRender(true);
	}
	return true;
}

DateTime::DateTime() {
	_digital = new DigitalClocks();
	_clocks = new AnalogClocks();
}

