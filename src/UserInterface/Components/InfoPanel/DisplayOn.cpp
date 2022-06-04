#include "config.h"

#include "DisplayOn.h"

#include <LilyGoWatch.h>

#include "System/AppsStatusMonitor.h"
#include "UserInterface/Icons/LightBulb.h"
#include "UserInterface/UserInterfaceManager.h"

void DisplayOn::render() {

	if (AppsStatusMonitor::getInstance()->isDateTimeAlwaysOn() != this->prevState) {
		if (AppsStatusMonitor::getInstance()->isDateTimeAlwaysOn() == true) {
			UserInterfaceManager::getInstance()->renderIcon(iconLightBulb, POS_X, POS_Y);
		} else {
			TTGOClass::getWatch()->tft->fillRect(POS_X, POS_Y, 18, 22, COLOR_BACKGROUND);
		}
		this->prevState = AppsStatusMonitor::getInstance()->isDateTimeAlwaysOn();
	}
}