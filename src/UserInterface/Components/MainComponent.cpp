#include "MainComponent.h"

void MainComponent::setShouldReRender(bool shouldReRender) {
	this->shouldRerender = shouldReRender;
}

bool MainComponent::shouldReRender() {
	return this->shouldRerender;
}
