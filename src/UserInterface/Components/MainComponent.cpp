#include "MainComponent.h"

void MainComponent::setShouldReRender(bool shouldReRender = true) {
	this->shouldRerender = shouldReRender;
}

bool MainComponent::shouldReRender() {
	return this->shouldRerender;
}
