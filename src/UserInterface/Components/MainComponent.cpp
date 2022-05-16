#include "MainComponent.h"

void MainComponent::setShouldReRender(bool shouldReRender = true) {
	_shouldReRender = shouldReRender;
}

bool MainComponent::shouldReRender() {
	return _shouldReRender;
}