#include "BatteryLeveLWarningsListener.h"

#include "config.h"

#include "Events/EventManager.h"
#include "Core/Hardware/MotorController.h"
#include "Core/Hardware/BatteryManager.h"
#include "Core/InactivityWatcher.h"

bool BatteryLeveLWarningsListener::listen(uint8_t event) {
	return event == EVENT_BATTERY_CHANGE;
}

void BatteryLeveLWarningsListener::handle() {
	int32_t vibrationCount = 0;
	uint8_t capacity = BatteryManager::getInstance()->getCapacity();
	if (BatteryManager::getInstance()->isCharging() == true) {
		this->batteryLowWarnVibrateOnLevel = 101;
	} else {
		if (capacity == (uint8_t)BATTERY_LOW) {
			vibrationCount = 1;
		}

		if (capacity == (uint8_t)BATTERY_VERY_LOW) {
			vibrationCount = 2;
		}

		if (
			(vibrationCount > 0)
			&& (capacity < this->batteryLowWarnVibrateOnLevel)
		) {
			InactivityWatcher::getInstance()->markActivity();
			MotorController::vibrate(vibrationCount);
			this->batteryLowWarnVibrateOnLevel = capacity;
		}
	}
}
