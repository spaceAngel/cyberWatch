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
	_digital->setShouldReRender(shouldReRender);
	_clocks->setShouldReRender(shouldReRender);
	_planetoid->setShouldReRender(shouldReRender);
}

bool DateTime::handleVerticalSwipe(int8_t vector) {
	_currentFace += vector;
	if (_currentFace > FACES) {
		_currentFace = 1;
	}
	if (_currentFace == 0) {
		_currentFace = FACES;
	}

	getCurrentFace()->setShouldReRender(true);
	return true;
}

MainComponent *DateTime::getCurrentFace() {
	MainComponent *component;
	if (_currentFace == FACE_ANALOG) { component = _clocks; }
	if (_currentFace == FACE_DIGITAL) { component = _digital; }
	if (_currentFace == FACE_PLANETOID) { component = _planetoid; }
	return component;
}

DateTime::DateTime() {
	_digital = new DigitalClocks();
	_clocks = new AnalogClocks();
	_planetoid = new Planetoid();
}

