#include "DigitalClocks.h"

#include "Apps/WatchFaces/Components/Date.h"
#include "Apps/WatchFaces/Components/Time.h"

void DigitalClocks::render() {
	this->date->render();
	this->time->render();
}

void DigitalClocks::setShouldReRender(bool shouldReRender) {
	this->date->setShouldReRender(shouldReRender);
	this->time->setShouldReRender(shouldReRender);
}

DigitalClocks::DigitalClocks() {
	this->time = new Time();
	this->date = new Date();
}