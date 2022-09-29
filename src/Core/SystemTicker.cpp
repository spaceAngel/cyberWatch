#include "SystemTicker.h"

#include "config.h"

#include "Core/Hardware/RTC.h"
#include "Core/Hardware/BatteryManager.h"

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
	BatteryManager::getInstance()->getCapacity();
	this->ticks++;
}

void SystemTicker::tickSleep() {
	for (uint16_t i = 0; i <  (uint8_t)((SLEEPCYCLE_MS * CPU_FREQUENCY_LOW) / 1000); i++) {
		this->tickWakedUp();
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