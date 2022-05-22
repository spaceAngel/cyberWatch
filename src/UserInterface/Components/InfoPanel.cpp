#include "config.h"

#include "InfoPanel.h"

void InfoPanel::render() {
	_battery->render();
	_stepCounter->render();
	_runningStopWatch->render();
};
