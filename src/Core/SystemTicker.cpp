#include "SystemTicker.h"

#include "config.h"

SystemTicker* SystemTicker::inst;

SystemTicker *SystemTicker::getInstance() {

	if (SystemTicker::inst == nullptr) {
		SystemTicker::inst = new SystemTicker();
	}
	return SystemTicker::inst;
}

void SystemTicker::tickWakedUp() {
	if (this->ticks == USHRT_MAX) {
		this->ticks = 0;
	}
	this->ticks++;
}

void SystemTicker::tickSleep() {
	for (uint16_t i; i < (TICK_SLEEP / TICK_WAKEUP); i++)  {
		this->tickWakedUp();
	}
}

bool SystemTicker::isTickFor(uint16_t tickCount) {
	return (this->ticks % tickCount) == 0;
}
