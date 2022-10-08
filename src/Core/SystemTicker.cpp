#include "SystemTicker.h"

#include "config.h"

SystemTicker* SystemTicker::inst;

void IRAM_ATTR onTickerTimer() {
	SystemTicker::getInstance()->tickWakedUp();
}

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

SystemTicker::SystemTicker() {
	this->timer = timerBegin(0, CPU_FREQUENCY_LOW, true);
	timerAttachInterrupt(this->timer, &onTickerTimer, true);
	timerAlarmWrite(this->timer, 50000, true);
	timerAlarmEnable(this->timer);
}