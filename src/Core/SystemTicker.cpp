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
	if (this->ticks > this->maxTicks) {
		this->ticks = 0;
	}
	RTC::getInstance()->getCurrentDate();
	this->ticks++;
}

void SystemTicker::tickSleep() {
	this->ticks += (uint8_t)((SLEEPCYCLE_MS * CPU_FREQUENCY_LOW) / 1000);
	if (this->ticks > this->maxTicks) {
		this->ticks = 0;
	}
}

bool SystemTicker::isTickFor(uint16_t tickCount) {
	this->setMaxTicks(tickCount);
	return (this->ticks % tickCount) == 0;
}

void SystemTicker::setMaxTicks(uint16_t maxTicks) {
	if (this->maxTicks < maxTicks) {
		this->maxTicks = maxTicks;
	}
}