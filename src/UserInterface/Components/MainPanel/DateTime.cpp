#include "config.h"

#include <LilyGoWatch.h>

#include "DateTime.h"
#include "UserInterface/Components/MainPanel/DateTime/DigitalClocks.h"
#include "UserInterface/Components/MainPanel/DateTime/AnalogClocks.h"
#include "UserInterface/Components/MainPanel/DateTime/Planetoid.h"
#include "UserInterface/Components/MainComponent.h"

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

	getCurrentFace()->setShouldReRender(true);
	return true;
}

MainComponent *DateTime::getCurrentFace() {
	return this->clockFaces[this->currentFace];
}
