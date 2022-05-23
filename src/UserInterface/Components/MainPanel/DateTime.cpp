#include "config.h"

#include <LilyGoWatch.h>

#include "DateTime.h"
#include "UserInterface/Components/MainPanel/DateTime/Date.h"
#include "UserInterface/Components/MainPanel/DateTime/Time.h"

void DateTime::render() {
	_date->render();
	_time->render();
}

void DateTime::setShouldReRender(bool shouldReRender) {
	_date->setShouldReRender(shouldReRender);
	_time->setShouldReRender(shouldReRender);
}

DateTime::DateTime() {
	_date = new Date();
	_time = new Time();
}

