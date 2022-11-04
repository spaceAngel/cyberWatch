#include "config.h"

#include <LilyGoWatch.h>

#include "Charger.h"
#include "Core/Hardware/BatteryManager.h"

#include "UserInterface/Icons/Charging.h"
#include "UserInterface/UserInterfaceManager.h"

void Charger::render() {
	if (BatteryManager::getInstance()->isCharging() != this->prevChargingState) {
		if (BatteryManager::getInstance()->isCharging() == true) {
			UserInterfaceManager::getInstance()->renderIcon(iconCharging, 140, this->posY);
		} else {
			TTGOClass::getWatch()->tft->fillRect(140, this->posY, 24, 24, COLOR_BACKGROUND);
		}
		this->prevChargingState = BatteryManager::getInstance()->isCharging();
	}
}
