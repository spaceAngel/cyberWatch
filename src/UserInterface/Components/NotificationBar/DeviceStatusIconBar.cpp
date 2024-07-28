#include "config.h"

#include "DeviceStatusIconBar.h"

#include "UserInterface/UserInterfaceManager.h"

#include <LilyGoWatch.h>

#include "UserInterface/Icons/IconStruct.h"
#include "UserInterface/Icons/Charging.h"
#include "UserInterface/Icons/LightBulb.h"
#include "UserInterface/Icons/StopWatch.h"
#include "UserInterface/Icons/Lock.h"
#include "UserInterface/Icons/Bell.h"

#include "Apps/StopWatch/StopWatchRegistry.h"
#include "Environment/AppSettings.h"
#include "Core/Hardware/BatteryManager.h"
#include "Apps/Alarm/AlarmStorage.h"
#include "Environment/SystemInfo.h"

void DeviceStatusIconBar::render() {
	if (
		this->prevBits != this->getDeviceStateBitMask()
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(
			RESOLUTION_WIDTH - 147,
			0,
			100,
			24,
			COLOR_BACKGROUND
		);
		uint8_t pos = 0;
		this->renderIconCharging(pos);
		this->renderIconDisplayAlwaysOn(pos);
		this->renderIconStopwatchRunning(pos);
		this->renderIconDisplayLocked(pos);
		this->renderIconAlarmEnabled(pos);
		this->prevBits = this->getDeviceStateBitMask();
		this->setShouldReRender(false);
	}
}

void DeviceStatusIconBar::renderIcon(IconStruct icon, uint8_t &pos) {

	UserInterfaceManager::getInstance()->renderIcon(
		icon,
		RESOLUTION_WIDTH - 72 - (pos * 25),
		2
	);
	pos++;
}

uint8_t DeviceStatusIconBar::getDeviceStateBitMask() {
	uint8_t bits = 0;
	if (StopWatchRegistry::getInstance()->getRunning()) {
		bits |= DEVICESTATE_NOTIFICATIONS_STOPWATCH_RUNNING;
	}

	if (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON)) {
		bits |= DEVICESTATE_NOTIFICATIONS_DISPLAY_ALWAYS_ON;
	}

	if (BatteryManager::getInstance()->isCharging()) {
		bits |= DEVICESTATE_NOTIFICATIONS_CHARGING;
	}

	if (BatteryManager::getInstance()->isCharging()) {
		bits |= DEVICESTATE_NOTIFICATIONS_CHARGING;
	}

	if (UserInterfaceManager::getInstance()->isLocked() == true) {
		bits |= DEVICESTATE_NOTIFICATIONS_DISPLAY_LOCKED;
	}

	if (AlarmStorage::getInstance()->isActiveAlarm()) {
		bits |= DEVICESTATE_NOTIFICATIONS_ALARM_ENABLED;
	}

	return bits;
}

void DeviceStatusIconBar::renderIconCharging(uint8_t &pos) {
	if (
		BatteryManager::getInstance()->isCharging()
		|| SystemInfo::getInstance()->getPluggedIn()
	) {
		this->renderIcon(iconCharging, pos);
	}
}

void DeviceStatusIconBar::renderIconDisplayAlwaysOn(uint8_t &pos) {
	if (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON)) {
		this->renderIcon(iconLightBulb, pos);
	}
}

void DeviceStatusIconBar::renderIconStopwatchRunning(uint8_t &pos) {
	if (StopWatchRegistry::getInstance()->getRunning()) {
		this->renderIcon(iconStopWatch, pos);
	}
}

void DeviceStatusIconBar::renderIconDisplayLocked(uint8_t &pos) {
	if (UserInterfaceManager::getInstance()->isLocked() == true) {
		this->renderIcon(iconLock, pos);
	}
}

void DeviceStatusIconBar::renderIconAlarmEnabled(uint8_t &pos) {
	if (AlarmStorage::getInstance()->isActiveAlarm()) {
		this->renderIcon(iconBell, pos);
	}
}
