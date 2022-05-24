#include "config.h"

#include <LilyGoWatch.h>

#include "MainPanel.h"

void MainPanel::render() {
	getCurrentComponent()->render();
};

void MainPanel::switchScreen(int vector) {
	_currentComponent += vector;
	if (_currentComponent > COMPONENTS) {
		_currentComponent = 1;
	}
	if (_currentComponent == 0) {
		_currentComponent = COMPONENTS;
	}

	getCurrentComponent()->setShouldReRender(true);
	_clear();
	render();
}

void MainPanel::handleSwipeVertical(int vector) {
	MainComponent *component;
	bool handle = false;
	if (_currentComponent == COMPONENT_CALENDAR) { handle = true; component = _calendar;}

	if (handle) {
		if (component->handleVerticalSwipe(vector)) {
			_clear();
		}
	}
}

void MainPanel::_clear() {
	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		TTGOClass::getWatch()->tft->width(),
		150,
		TFT_BLACK
	);
}

void MainPanel::handlePEKShort() {
	MainComponent *component;
	bool handle = false;
	if (_currentComponent == COMPONENT_CALENDAR) { handle = true; component = _calendar;}
	if (_currentComponent == COMPONENT_STOPWATCH) { handle = true; component = _stopWatch;}

	if (handle) {
		if (component->handlePEKShort()) {
			_clear();
		}
	}
}

bool MainPanel::isSleepForbidden() {
	return
		_currentComponent == COMPONENT_STOPWATCH
	;
}

MainComponent *MainPanel::getCurrentComponent() {
	MainComponent *component;
	if (_currentComponent == COMPONENT_DATETIME) { component = _dateTime; }
	if (_currentComponent == COMPONENT_CALENDAR) { component = _calendar; }
	if (_currentComponent == COMPONENT_STOPWATCH) { component = _stopWatch; }
	return component;
}