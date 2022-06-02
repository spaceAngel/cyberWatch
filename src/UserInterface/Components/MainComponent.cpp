#include "MainComponent.h"

void MainComponent::setShouldReRender(bool shouldReRender) {
	this->shouldRerender = shouldReRender;
}

bool MainComponent::shouldReRender() {
	return this->shouldRerender;
}

void MainComponent::setIsActive(bool isActive) {
	this->isActive = isActive;
}

bool MainComponent::getIsActive() {
	return this->isActive;
}