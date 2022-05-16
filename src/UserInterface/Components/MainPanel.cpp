#include "config.h"

#include <LilyGoWatch.h>

#include "MainPanel.h"

void MainPanel::render() {
	if (_currentComponent == COMPONENT_DATETIME) {
		_date->render();
		_time->render();
	}
};

void MainPanel::switchScreen(int vector) {
	_currentComponent += vector;
	if (_currentComponent > COMPONENTS) {
		_currentComponent = 1;
	}
	if (_currentComponent == 0) {
		_currentComponent = COMPONENTS;
	}
	if (_currentComponent == COMPONENT_DATETIME) {
		_date->setShouldReRender(true);
		_time->setShouldReRender(true);
	}
	_clear();
	render();
}

void MainPanel::_clear() {
	TTGOClass::getWatch()->tft->fillRect(
		0,
		18,
		TTGOClass::getWatch()->tft->width(),
		116,
		TFT_BLACK
	);
}
