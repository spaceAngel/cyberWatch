#include "DigitalClocks.h"

#include "UserInterface/Components/MainPanel/DateTime/SubComponents/Date.h"
#include "UserInterface/Components/MainPanel/DateTime/SubComponents/Time.h"

void DigitalClocks::render() {
	_date->render();
	_time->render();
}

void DigitalClocks::setShouldReRender(bool shouldReRender) {
	_date->setShouldReRender(shouldReRender);
	_time->setShouldReRender(shouldReRender);
}

DigitalClocks::DigitalClocks() {
	_time = new Time();
	_date = new Date();
}