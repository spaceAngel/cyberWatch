#pragma once

#include <WiFi.h>

class BatteryManager {

  public:
  
    static BatteryManager *getInstance()
    {

        if (BatteryManager::_inst == nullptr) {
            BatteryManager::_inst = new BatteryManager();
        }
        return BatteryManager::_inst;
    }

    uint getCapacity() {
      return TTGOClass::getWatch()->power->getBattPercentage();
    }

    bool isCharging() {
      return TTGOClass::getWatch()->power->isChargeing();
    }

    bool handleCabelPlugIRQ() {
      return (
        TTGOClass::getWatch()->power->isVbusRemoveIRQ()
        || TTGOClass::getWatch()->power->isVbusPlugInIRQ()
        || TTGOClass::getWatch()->power->isAcinRemoveIRQ()
        || TTGOClass::getWatch()->power->isAcinPlugInIRQ()
      );
    }

    void energyConsumptionSavingsSettings() {
      WiFi.disconnect(true);  // Disconnect from the network
      WiFi.mode(WIFI_OFF);      // Switch WiFi off //not need to wifi on -> power saving
    }

  protected:

      static BatteryManager *_inst;

      long _lastActivity;

      BatteryManager() {
      }

};

BatteryManager* BatteryManager::_inst;
