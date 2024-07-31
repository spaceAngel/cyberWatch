#include "config.h"
#include "LcarsWatchStateIndicator.h"

#include <LilyGoWatch.h>
#include "UserInterface/UserInterfaceManager.h"
#include "Environment/AppSettings.h"
#include "Apps/Alarm/AlarmStorage.h"

void LcarsWatchStateIndicator::render() {
	if (
		this->shouldReRender()
		 || AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) != this->prevDisplay
		 || UserInterfaceManager::getInstance()->isLocked() != this->prevLock
		 || AlarmStorage::getInstance()->isActiveAlarm() != this->prevAlarm
	) {
		TTGOClass::getWatch()->tft->fillRect(52, 169, 120, 20, TFT_BLACK);

		TTGOClass::getWatch()->tft->setTextColor(AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON) ? TFT_PINK : TFT_DARKGREY);
		TTGOClass::getWatch()->tft->drawString("DSP", 52, 169);

		TTGOClass::getWatch()->tft->setTextColor(UserInterfaceManager::getInstance()->isLocked() ? TFT_PINK : TFT_DARKGREY);
		TTGOClass::getWatch()->tft->drawString("LCK", 113, 169);

		TTGOClass::getWatch()->tft->setTextColor(AlarmStorage::getInstance()->isActiveAlarm() ? TFT_PINK : TFT_DARKGREY);
		TTGOClass::getWatch()->tft->drawString("ALM", 172, 169);

		this->setShouldReRender(false);;
		this->prevDisplay = AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON);
		this->prevLock = UserInterfaceManager::getInstance()->isLocked();
		this->prevAlarm = AlarmStorage::getInstance()->isActiveAlarm();
	}
}