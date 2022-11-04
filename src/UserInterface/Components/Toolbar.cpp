#include "config.h"

#include "Toolbar.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/Icons/Battery.h"

void Toolbar::render() {
	this->renderDesign();
	this->battery->render();
}

void Toolbar::renderDesign() {
	if (this->shouldReRender()) {
		TTGOClass::getWatch()->tft->drawLine(
			0,
			26,
			TTGOClass::getWatch()->tft->width(),
			26,
			COLOR_MAIN_3
		);
	}
}

Toolbar::Toolbar() {
	this->battery = new Battery(
		TTGOClass::getWatch()->tft->width() - 45,
		0,
		false
	);
}

void Toolbar::setShouldReRender(bool shouldReRender) {
	this->battery->setShouldReRender(shouldReRender);
	MainComponent::setShouldReRender(shouldReRender);
}
