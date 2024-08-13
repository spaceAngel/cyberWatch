#include "config.h"

#include <LilyGoWatch.h>

#include "DeusEx.h"
#include "Core/Hardware/RTC.h"
#include "Core/Hardware/Display.h"
#include "Utils/DateUtil.h"
#include "UserInterface/BackgroundRenderer.h"
#include "Core/Hardware/BatteryManager.h"
#include "UserInterface/UserInterfaceManager.h"
#include "Apps/Alarm/AlarmStorage.h"
#include "Environment/AppSettings.h"
#include "Environment/SystemInfo.h"

#include "DeusEx/Lock.h"
#include "DeusEx/Display.h"
#include "DeusEx/Alarm.h"
#include "DeusEx/Plug.h"

void DeusEx::render() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	if (
		(this->prevMinute != currentTime.minute)
		|| (this->shouldReRender())
	) {
		this->setShouldReRender(true); // due to renderDeviceState / renderBattery,... when !should && prevminute != minute
		this->prevMinute = currentTime.minute;
		BackgroundRenderer::renderImage(BACKGROUND_WATCH_DEUSEX);
		TTGOClass::getWatch()->tft->setTextColor(TFT_WHITE);

		this->renderTime();
		this->renderDate();
		Display::getInstance()->resetTypographySettings();
	}
	this->renderDeviceStateIcons();
	this->renderBatteryInfo();
	this->setShouldReRender(false);
	Display::getInstance()->resetTypographySettings();
}

void DeusEx::renderBatteryInfo() {
	uint8_t battery = BatteryManager::getInstance()->getCapacity();
	if (
		this->shouldReRender()
		|| (battery != this->prevBattery)
		|| (this->prevCabelPlugged != SystemInfo::getInstance()->getPluggedIn())
	) {
		TTGOClass::getWatch()->tft->fillRect(80, 02, 144, 22, 0x2124);
		char batteryStr[9];
		TTGOClass::getWatch()->tft->setTextColor(TFT_WHITE);
		(void)snprintf(batteryStr, sizeof(batteryStr), "BAT %d%%", battery);
		TTGOClass::getWatch()->tft->drawString(batteryStr, 104, 04);

		if(SystemInfo::getInstance()->getPluggedIn()) {
			TTGOClass::getWatch()->tft->pushImage(80, 02, iconPlug.width, iconPlug.heigth, iconPlug.data);
		}
	}
	this->prevBattery = battery;
	this->prevCabelPlugged = SystemInfo::getInstance()->getPluggedIn();
}

uint8_t DeusEx::getDeviceStateBitMask() {
	uint8_t bits = 0;

	if (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON)) {
		bits |= DEUSEX_DEVICESTATE_DISPLAYON;
	}

	if (UserInterfaceManager::getInstance()->isLocked() == true) {
		bits |= DEUSEX_DEVICESTATE_LOCKED;
	}

	if (AlarmStorage::getInstance()->isActiveAlarm()) {
		bits |= DEUSEX_DEVICESTATE_ALARM;
	}

	return bits;
}

void DeusEx::renderDeviceStateIcons() {
	if (
		this->shouldReRender()
		|| this->getDeviceStateBitMask() != this->prevBitMask
	) {
		TTGOClass::getWatch()->tft->fillRect(120, ICONS_POS_Y, 100, 22, 0x2124);
		if (UserInterfaceManager::getInstance()->isLocked()) {
			TTGOClass::getWatch()->tft->pushImage(126, ICONS_POS_Y, iconLock.width, iconLock.heigth, iconLock.data);
		}

		if (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON)) {
			TTGOClass::getWatch()->tft->pushImage(148, ICONS_POS_Y, iconDisplay.width, iconDisplay.heigth, iconDisplay.data);
		}

		if (AlarmStorage::getInstance()->isActiveAlarm()) {
			TTGOClass::getWatch()->tft->pushImage(170, ICONS_POS_Y, iconAlarm.width, iconAlarm.heigth, iconAlarm.data);
		}
	}
	this->prevBitMask = this->getDeviceStateBitMask();
}

void DeusEx::renderTime() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	char timeStr[6];
	(void)snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);
	TTGOClass::getWatch()->tft->setTextFont(6);
	TTGOClass::getWatch()->tft->setTextSize(2);
	TTGOClass::getWatch()->tft->drawString(
		timeStr,
		0,
		56
	);
}

void DeusEx::renderDate() {
	RTC_Date currentDate = RTC::getInstance()->getCurrentDate();
	char dateStr[10];
	char dayInWeek[4];
	DateUtil::weekdayNameShort(dayInWeek, currentDate.year,currentDate.month, currentDate.day);
	(void)snprintf(dateStr, sizeof(dateStr), "%s %02d/%02d",dayInWeek, currentDate.day, currentDate.month);
	uint8_t dateStringWidth = TTGOClass::getWatch()->tft->textWidth(dateStr);
	TTGOClass::getWatch()->tft->setTextFont(4);
	TTGOClass::getWatch()->tft->setTextSize(2);
	TTGOClass::getWatch()->tft->drawString(
		dateStr,
		1,
		145
	);
}