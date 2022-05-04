#pragma once

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

  protected:

      static BatteryManager *_inst;

      const long INACTIVITY_TRESHOLD = 5000;

      long _lastActivity;

      BatteryManager() {
      }

};

BatteryManager* BatteryManager::_inst;
