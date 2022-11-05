#include "config.h"

#include "NotificationBar.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/Icons/Battery.h"
#include "UserInterface/Components/NotificationBar/DeviceStatusIconBar.h"

#include "Core/Hardware/MotorController.h"

void NotificationBar::render() {
	this->renderDesign();
	this->battery->render();
	this->deviceStatusIconBar->render();
}

void NotificationBar::renderDesign() {
	if (this->shouldReRender()) {

	}
}

NotificationBar::NotificationBar() {
	this->battery = new Battery(
		TTGOClass::getWatch()->tft->width() - 45,
		0,
		false
	);
	this->deviceStatusIconBar = new DeviceStatusIconBar();
}

void NotificationBar::setShouldReRender(bool shouldReRender) {
	this->battery->setShouldReRender(shouldReRender);
	this->deviceStatusIconBar->setShouldReRender(shouldReRender);
	MainComponent::setShouldReRender(shouldReRender);
}
