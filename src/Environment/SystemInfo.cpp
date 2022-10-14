#include "SystemInfo.h"
#include <time.h>

SystemInfo *SystemInfo::inst;

SystemInfo *SystemInfo::getInstance() {
	if (SystemInfo::inst == nullptr) {
		SystemInfo::inst = new SystemInfo();
	}
	return SystemInfo::inst;
}

SystemInfo::SystemInfo() {
	this->startAt = time(0);
}

uint SystemInfo::getUptime() {
	return time(0) - this->startAt;
}