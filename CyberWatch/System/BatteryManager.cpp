#include <sys/_stdint.h>
#pragma once

#include <WiFi.h>
#include "../../config.h"

class BatteryManager {

  public:
  
    static BatteryManager *getInstance()
    {

        if (BatteryManager::_inst == nullptr) {
            BatteryManager::_inst = new BatteryManager();
        }
        return BatteryManager::_inst;
    }

    uint8_t getCapacity() {
      int capacity = (int)(TTGOClass::getWatch()->power->getBattVoltage()  - BATTERY_LOW_CAPACITY) * 100 / (BATTERY_FULL_CAPACITY - BATTERY_LOW_CAPACITY);
      capacity = min(100, capacity);  //prevent to return capacity over 100% (calculation inaccurancy)
      capacity = max(0, capacity); //prevent to return capacity less then 0 (calculation inaccurancy)
      return (uint8_t)capacity;
    }

    bool isCharging() {
      return TTGOClass::getWatch()->power->isChargeing();
    }

    bool handleCabelPlugInIRQ() {
      return (
        TTGOClass::getWatch()->power->isVbusPlugInIRQ()
        || TTGOClass::getWatch()->power->isAcinPlugInIRQ()
      );
    }

    bool handleCabelPlugRemoveIRQ() {
      return (
        TTGOClass::getWatch()->power->isVbusRemoveIRQ()
        || TTGOClass::getWatch()->power->isAcinRemoveIRQ()
      );
    }

    void energyConsumptionSavingsSettings() {
      WiFi.disconnect(true);  // Disconnect from the network
      WiFi.mode(WIFI_OFF);      // Switch WiFi off //not need to wifi on -> power saving
      setCpuFrequencyMhz(CPU_FREQUENCY);
    }

  protected:

      static BatteryManager *_inst;

      long _lastActivity;

      BatteryManager() {
      }

};

BatteryManager* BatteryManager::_inst;
