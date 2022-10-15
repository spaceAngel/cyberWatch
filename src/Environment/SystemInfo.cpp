#include "SystemInfo.h"
#include <time.h>

#include "Core/Hardware/BatteryManager.h"

SystemInfo *SystemInfo::inst;

SystemInfo *SystemInfo::getInstance() {
	if (SystemInfo::inst == nullptr) {
		SystemInfo::inst = new SystemInfo();
	}
	return SystemInfo::inst;
}

void SystemInfo::setPlugState(bool state) {
	this->pluggedIn = state;
	if (state == false) {
		this->pluggedInAt = time(0);
	}
}

bool SystemInfo::getPluggedIn() {
	return this->pluggedIn;
}

uint SystemInfo::getUnplugTime() {
	return time(0) - this->pluggedInAt;
}

SystemInfo::SystemInfo() {
	this->startAt = time(0);
	this->pluggedInAt = time(0);
	this->pluggedIn = BatteryManager::getInstance()->isCharging();
}

uint SystemInfo::getUptime() {
	return time(0) - this->startAt;
}