#include "config.h"

#include "AlarmListener.h"

#include <LilyGoWatch.h>

#include "AlarmStorage.h"
#include "Events/EventManager.h"
#include "Core/Hardware/RTC.h"
#include "Screens/AlarmRinging.h"
#include "UserInterface/Screens/MainScreen.h"
#include "Core/InactivityWatcher.h"
#include "Core/Hardware/Display.h"
#include "Utils/DateUtil.h"
#include "Core/Hardware/MotorController.h"

bool AlarmListener::listen(uint8_t event) {
	return event == EVENT_TIME_CHANGE;
}

void AlarmListener::handle() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (this->prevMinute == currentTime.minute) {
		return;
	}
	this->prevMinute = currentTime.minute;
	uint8_t dayInWeek = DateUtil::weekday(currentTime.year, currentTime.month, currentTime.day);
	if (dayInWeek == 0) {dayInWeek == 6;}
	else {dayInWeek--;} //cause week days in AlarmSettingsDayButtons starts from Monday, it must be "recalculated"

	for (uint8_t i = 0; i < 3; i++) {
		if (AlarmStorage::getInstance()->getAlarm(i)->getEnabled()) {
			if (
				(
					AlarmStorage::getInstance()->getAlarm(i)->isRunningOnce()
					|| AlarmStorage::getInstance()->getAlarm(i)->getIsEnabledForDay(dayInWeek)
				)
				&& (
					currentTime.hour == AlarmStorage::getInstance()->getAlarm(i)->getHour()
					&& currentTime.minute == AlarmStorage::getInstance()->getAlarm(i)->getMinute()
				)
			) {
				Display::getInstance()->turnDisplayOn();
				MainScreen::getInstance()->setAppOnTop(
					new AlarmRinging(
						AlarmStorage::getInstance()->getAlarm(i)->getHour(),
						AlarmStorage::getInstance()->getAlarm(i)->getMinute()
					)
				);
				MainScreen::getInstance()->getCurrentApp()->setShouldReRender(true);
				InactivityWatcher::getInstance()->markActivity();
				if (AlarmStorage::getInstance()->getAlarm(i)->isRunningOnce()) {
					AlarmStorage::getInstance()->getAlarm(i)->setEnabled(false);

				}
			}
		}
	}
}
