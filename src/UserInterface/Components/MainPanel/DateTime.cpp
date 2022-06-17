#include "config.h"

#include <LilyGoWatch.h>

#include "DateTime.h"
#include "UserInterface/Components/MainComponent.h"
#include "System/Registry.h"

void DateTime::render() {
	getCurrentFace()->render();
}

void DateTime::setShouldReRender(bool shouldReRender) {
	for (int32_t i = 0; i <= FACES; i++) {
		this->clockFaces[i]->setShouldReRender(shouldReRender);
	}
}

bool DateTime::handleSwipeVertical(int8_t vector) {
	this->currentFace += vector;
	if (this->currentFace > FACES) {
		this->currentFace = 0;
	}
	if (this->currentFace < 0) {
		this->currentFace = FACES;
	}

	Registry::getInstance()->setValue(Registry::NAME_WATCH_FACE, this->currentFace);
	this->getCurrentFace()->setShouldReRender(true);
	return true;
}

MainComponent *DateTime::getCurrentFace() {
	return this->clockFaces[this->currentFace];
}

bool DateTime::handlePEKShort() {
	this->alwaysOn = !this->alwaysOn;
	return false;
}

bool DateTime::isSystemSleepForbidden() {
	return this->alwaysOn == true;
}

DateTime::DateTime() {
	this->createFaces();
	uint currentFace = Registry::getInstance()->getValue(Registry::NAME_WATCH_FACE);
	if (
		(currentFace >= 0)
		&& (currentFace <= FACES)
	) {
		this->currentFace = currentFace;
	}
}
