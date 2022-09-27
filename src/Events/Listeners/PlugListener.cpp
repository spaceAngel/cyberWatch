#include "PlugListener.h"

#include "Events/EventManager.h"
#include "Core/Hardware/MotorController.h"
#include "Core/InactivityWatcher.h"

bool PlugListener::listen(uint8_t event) {
	return event == EVENT_CABLE_PLUG
	|| event == EVENT_CABLE_UNPLUG;
}

void PlugListener::handle() {
	InactivityWatcher::getInstance()->markActivity();
	MotorController::vibrate(1);
}
