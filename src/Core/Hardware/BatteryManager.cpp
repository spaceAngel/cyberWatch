#include "config.h"

#include "BatteryManager.h"

#include <LilyGoWatch.h>
#include <WiFi.h>

#include "Core/SystemTicker.h"
#include "Events/EventManager.h"
#include "Core/Hardware/MotorController.h"

BatteryManager* BatteryManager::inst;

BatteryManager *BatteryManager::getInstance() {

	if (BatteryManager::inst == nullptr) {
		BatteryManager::inst = new BatteryManager();
	}
	return BatteryManager::inst;
}

uint8_t BatteryManager::getCapacity() {
	this->updateCapacity();
	return (uint8_t)this->lastCapacity;
}

uint8_t BatteryManager::getUpdatedCapacity() {
	return TTGOClass::getWatch()->power->getBattPercentage();
}

void BatteryManager::updateCapacity() {
	if (
		this->lastCapacity == 0
		|| SystemTicker::getInstance()->isTickFor(TICKER_BATTERY)
	) {
		int capacity = TTGOClass::getWatch()->power->getBattPercentage();
		if (capacity == 127) {
			capacity = (int)(TTGOClass::getWatch()->power->getBattVoltage() - BATTERY_LOW_CAPACITY) * 100 / (BATTERY_FULL_CAPACITY - BATTERY_LOW_CAPACITY);
		}
		capacity = min(100, capacity);  //prevent to return capacity over 100% (calculation inaccurancy)
		capacity = max(0, capacity); //prevent to return capacity less then 0 (calculation inaccurancy)
		uint8_t lastCapacity = this->lastCapacity; //prevent recursion
		this->lastCapacity = capacity;
		if (capacity != lastCapacity) {
			EventManager::getInstance()->fireEvent(EVENT_BATTERY_CHANGE);
		}
	}
}

bool BatteryManager::isCharging() {
	return TTGOClass::getWatch()->power->isChargeing();
}

bool BatteryManager::handleCabelPlugInIRQ() {
	return (
		TTGOClass::getWatch()->power->isVbusPlugInIRQ()
		|| TTGOClass::getWatch()->power->isAcinPlugInIRQ()
	);
}

bool BatteryManager::handleCabelPlugRemoveIRQ() {
	return (
		TTGOClass::getWatch()->power->isVbusRemoveIRQ()
		|| TTGOClass::getWatch()->power->isAcinRemoveIRQ()
	);
}

void BatteryManager::energyConsumptionSavingsSettings() {
	WiFi.disconnect(true);	// Disconnect from the network
	WiFi.mode(WIFI_OFF);			// Switch WiFi off //not need to wifi on -> power saving
	TTGOClass::getWatch()->power->setPowerOutPut(AXP202_LDO4, false); // audio
	setCpuFrequencyMhz(CPU_FREQUENCY_LOW);
}


BatteryManager::BatteryManager() {
}
