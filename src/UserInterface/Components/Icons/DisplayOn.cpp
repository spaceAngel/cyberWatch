#include "config.h"

#include "DisplayOn.h"

#include <LilyGoWatch.h>

#include "Environment/AppSettings.h"
#include "UserInterface/Icons/LightBulb.h"
#include "UserInterface/UserInterfaceManager.h"

void DisplayOn::render() {

	if (
		AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) != this->prevState
		|| this->shouldReRender()
	) {
		if (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) == true) {
			UserInterfaceManager::getInstance()->renderIcon(iconLightBulb, POS_X, POS_Y);
		} else {
			TTGOClass::getWatch()->tft->fillRect(POS_X, POS_Y, 18, 22, COLOR_BACKGROUND);
		}
		this->prevState = AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON);
		this->setShouldReRender(false);
	}
}