#include "config.h"

#include "AlarmOn.h"

#include <LilyGoWatch.h>

#include "Apps/Alarm/AlarmStorage.h"
#include "UserInterface/Icons/Bell.h"
#include "UserInterface/UserInterfaceManager.h"

void AlarmOn::render() {

	if (
		AlarmStorage::getInstance()->isActiveAlarm() != this->prevState
		|| this->shouldReRender()
	) {
		if (AlarmStorage::getInstance()->isActiveAlarm() == true) {
			UserInterfaceManager::getInstance()->renderIcon(iconBell, POS_X, POS_Y);
		} else {
			TTGOClass::getWatch()->tft->fillRect(POS_X, POS_Y, 22, 22, COLOR_BACKGROUND);
		}
		this->prevState = AlarmStorage::getInstance()->isActiveAlarm();
		this->setShouldReRender(false);
	}
}