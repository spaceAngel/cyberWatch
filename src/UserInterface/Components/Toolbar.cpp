#include "config.h"

#include "Toolbar.h"

#include <LilyGoWatch.h>

void Toolbar::render() {
	this->renderDesign();
}

void Toolbar::renderDesign() {
	if (this->shouldReRender()) {
		TTGOClass::getWatch()->tft->drawLine(
			0,
			20,
			TTGOClass::getWatch()->tft->width(),
			20,
			COLOR_MAIN_1
		);
	}
}

Toolbar::Toolbar() {

}
