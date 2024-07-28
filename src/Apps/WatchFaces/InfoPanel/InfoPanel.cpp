#include "config.h"

#include "InfoPanel.h"

void InfoPanel::render() {
	this->battery->render();
	this->charger->render();
	this->stepCounter->render();
	this->runningStopWatch->render();
	this->displayOn->render();
	this->lock->render();
	this->alarmOn->render();
};

void InfoPanel::setShouldReRender(bool shouldReRender) {
	this->battery->setShouldReRender(shouldReRender);
	this->displayOn->setShouldReRender(shouldReRender);
	this->runningStopWatch->setShouldReRender(shouldReRender);
	this->stepCounter->setShouldReRender(shouldReRender);
	this->lock->setShouldReRender(shouldReRender);
	this->alarmOn->setShouldReRender(shouldReRender);
}
