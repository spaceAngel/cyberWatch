#include "config.h"

#include "InfoPanel.h"

void InfoPanel::render() {
	this->battery->render();
	this->stepCounter->render();
	this->runningStopWatch->render();
	this->displayOn->render();
	this->lock->render();
};
