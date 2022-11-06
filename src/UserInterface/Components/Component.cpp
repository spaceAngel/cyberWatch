#include "Component.h"

void Component::setShouldReRender(bool shouldReRender) {
	this->shouldRerender = shouldReRender;
}

bool Component::shouldReRender() {
	return this->shouldRerender;
}

void Component::setIsActive(bool isActive) {
	this->isActive = isActive;
}

bool Component::getIsActive() {
	return this->isActive;
}