#pragma once

#include "Display/Display.cpp"
#include "System/InactivityWatcher.cpp"
#include <LilyGoWatch.h>
#include <WiFi.h>



class CyberWatch {

  public:
    static CyberWatch *getInstance()
    {

        if (CyberWatch::_inst == nullptr) {
            CyberWatch::_inst = new CyberWatch();
        }
        return CyberWatch::_inst;
    }
  

    void init() {
      Serial.begin(9600);
      Serial.println("cyberWatch starting");

      TTGOClass::getWatch()->begin();
      Display::getInstance()->init();
         
      _setBatteryConsumptionSaving();
      _initInterrupts();
    };


    void loop() {
      int16_t x, y;
      uint unused = 0;
      while(1) {
        InactivityWatcher::getInstance()->checkInactivity();
        if (TTGOClass::getWatch()->getTouch(x, y)) {
          InactivityWatcher::getInstance()->markActivity();
        }
        Display::getInstance()->render();
        delay(TICK);      
      }
    };

  protected:
    static CyberWatch *_inst;

    const float TICK = 10;

    CyberWatch() {
    }

    void _setBatteryConsumptionSaving() {
      WiFi.disconnect(true);  // Disconnect from the network
      WiFi.mode(WIFI_OFF);      // Switch WiFi off //not need to wifi on -> power saving
    }

    void _initInterrupts() {
      pinMode(AXP202_INT, INPUT_PULLUP);
      attachInterrupt(
        AXP202_INT, 
        [] {},
        FALLING
      );
      TTGOClass::getWatch()->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);
      TTGOClass::getWatch()->power->clearIRQ();
      pinMode(TOUCH_INT, INPUT);
    }
    
};

CyberWatch* CyberWatch::_inst;
