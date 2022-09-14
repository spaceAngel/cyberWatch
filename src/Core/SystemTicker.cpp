#include "SystemTicker.h"

#include "config.h"


#include "Core/Hardware/RTC.h"

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
	RTC::getInstance()->getCurrentDate();
	this->ticks++;
}

void SystemTicker::tickSleep() {
	this->ticks += (uint8_t)((SLEEPCYCLE_MS / 1000) * TICK_WAKEUP);
	if (this->ticks == USHRT_MAX) {
		this->ticks = 0;
	}
}

bool SystemTicker::isTickFor(uint16_t tickCount) {
	return (this->ticks % tickCount) == 0;
}
