#pragma once

#include "../Display/Display.cpp"

class InactivityWatcher {

  public:
  
    static InactivityWatcher *getInstance()
    {

        if (InactivityWatcher::_inst == nullptr) {
            InactivityWatcher::_inst = new InactivityWatcher();
        }
        return InactivityWatcher::_inst;
    }

    void checkInactivity() {
      if (_lastActivity + INACTIVITY_TRESHOLD < millis()) {
        Display::getInstance()->turnDisplayOff();

            TTGOClass::getWatch()->power->setPowerOutPut(AXP202_LDO3, false);
            TTGOClass::getWatch()->power->setPowerOutPut(AXP202_LDO4, false);
            TTGOClass::getWatch()->power->setPowerOutPut(AXP202_EXTEN, false);
            TTGOClass::getWatch()->power->setPowerOutPut(AXP202_DCDC2, false);

            esp_sleep_enable_ext1_wakeup(GPIO_SEL_38, ESP_EXT1_WAKEUP_ALL_LOW);
            TTGOClass::getWatch()->power->clearIRQ();
            esp_light_sleep_start();
      }
    }

    void markActivity() {
      _lastActivity = millis();
      Display::getInstance()->turnDisplayOn();
    }
  
    protected:

      static InactivityWatcher *_inst;

      const long INACTIVITY_TRESHOLD = 5000;

      long _lastActivity;

      InactivityWatcher() {
        _lastActivity = millis();
      }

};

InactivityWatcher* InactivityWatcher::_inst;
