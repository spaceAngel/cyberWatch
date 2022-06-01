#include "config.h"

#include <LilyGoWatch.h>

#include "MainPanel.h"

void MainPanel::render() {
	this->getCurrentComponent()->render();
};

void MainPanel::switchScreen(int vector) {
	this->currentComponent += vector;
	if (this->currentComponent > COMPONENTS) {
		this->currentComponent = 1;
	}
	if (this->currentComponent == 0) {
		this->currentComponent = COMPONENTS;
	}

	this->getCurrentComponent()->setShouldReRender(true);
	this->clear();
	this->render();
}

void MainPanel::handleSwipeVertical(int8_t vector) {
	MainComponent *component;
	bool handle = false;
	if (this->currentComponent == COMPONENT_CALENDAR) { handle = true; component = this->calendar;}
	if (this->currentComponent == COMPONENT_DATETIME) { handle = true; component = this->dateTime;}

	if (handle) {
		if (component->handleSwipeVertical(vector) == true) {
			this->clear();
		}
	}
}

void MainPanel::clear() {
	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		TTGOClass::getWatch()->tft->width(),
		150,
		COLOR_BACKGROUND
	);

}

void MainPanel::handlePEKShort() {
	MainComponent *component;
	bool handle = false;
	if (this->currentComponent == COMPONENT_CALENDAR) { handle = true; component = this->calendar;}
	if (this->currentComponent == COMPONENT_STOPWATCH) { handle = true; component = this->stopWatch;}

	if (handle) {
		if (component->handlePEKShort() == true) {
			this->clear();
		}
	}
}

bool MainPanel::isSleepForbidden() {
	return
		this->currentComponent == COMPONENT_STOPWATCH
	;
}

MainComponent *MainPanel::getCurrentComponent() {
	MainComponent *component = new MainComponent();
	if (this->currentComponent == COMPONENT_DATETIME) { component = this->dateTime; }
	if (this->currentComponent == COMPONENT_CALENDAR) { component = this->calendar; }
	if (this->currentComponent == COMPONENT_STOPWATCH) { component = this->stopWatch; }
	return component;
}