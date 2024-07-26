#include "config.h"

#include <LilyGoWatch.h>

#include "Charger.h"
#include "Core/Hardware/BatteryManager.h"

#include "UserInterface/Icons/Charging.h"
#include "UserInterface/UserInterfaceManager.h"
#include "Environment/SystemInfo.h"

void Charger::render() {
	bool state = BatteryManager::getInstance()->isCharging() ||  SystemInfo::getInstance()->getPluggedIn();
	if ( state!= this->prevChargingState) {
		if (state) {
			UserInterfaceManager::getInstance()->renderIcon(iconCharging, 140, this->posY);
		} else {
			TTGOClass::getWatch()->tft->fillRect(140, this->posY, 24, 24, COLOR_BACKGROUND);
		}
		this->prevChargingState = state;
	}
}
