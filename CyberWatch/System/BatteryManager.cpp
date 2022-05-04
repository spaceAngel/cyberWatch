#pragma once

#include "../Display/Display.cpp"

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

  protected:

      static BatteryManager *_inst;

      const long INACTIVITY_TRESHOLD = 5000;

      long _lastActivity;

      BatteryManager() {
      }

};

BatteryManager* BatteryManager::_inst;
