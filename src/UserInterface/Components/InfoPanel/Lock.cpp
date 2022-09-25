#include "config.h"

#include "Lock.h"

#include <LilyGoWatch.h>

#include "Environment/AppSettings.h"
#include "UserInterface/Icons/Lock.h"
#include "UserInterface/UserInterfaceManager.h"

void Lock::render() {

	if (UserInterfaceManager::getInstance()->isLocked() != this->prevState) {
		if (UserInterfaceManager::getInstance()->isLocked() == true) {
			UserInterfaceManager::getInstance()->renderIcon(iconLock, POS_X, POS_Y);
		} else {
			TTGOClass::getWatch()->tft->fillRect(POS_X, POS_Y, 18, 22, COLOR_BACKGROUND);
		}
		this->prevState = UserInterfaceManager::getInstance()->isLocked();
	}
}