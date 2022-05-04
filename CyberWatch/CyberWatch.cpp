#pragma once

#include "Display/Display.cpp"
#include "System/InactivityWatcher.cpp"
#include <LilyGoWatch.h>
#include <WiFi.h>
#include "soc/rtc_wdt.h"

bool esp32IRQ = false;

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
      TTGOClass::getWatch()->motor_begin();
      Display::getInstance()->init();
         
      _setBatteryConsumptionSaving();
      _initEsp32Interrupts();
      _initStepCounter();
      Display::getInstance()->showSplashScreen();
    };

    void loop() {
      int16_t x, y;
      uint unused = 0;
      while(1) {
        if (esp32IRQ) {
          esp32IRQ = false;
          TTGOClass::getWatch()->power->readIRQ();
          _handleBatteryIRQ();
          TTGOClass::getWatch()->power->clearIRQ();
        }
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

    void _initEsp32Interrupts() {
      pinMode(AXP202_INT, INPUT_PULLUP);
      attachInterrupt(
        AXP202_INT, 
        [] {
          esp32IRQ = true;
        },
        FALLING
      );
      TTGOClass::getWatch()->power->enableIRQ(
        AXP202_PEK_SHORTPRESS_IRQ &
        AXP202_VBUS_REMOVED_IRQ & AXP202_VBUS_CONNECT_IRQ &
        AXP202_ACIN_REMOVED_IRQ & AXP202_ACIN_CONNECT_IRQ,
        true
      );
      TTGOClass::getWatch()->power->clearIRQ();
      pinMode(TOUCH_INT, INPUT);;
    }

    void _initStepCounter() {
      Acfg cfg;
      cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
      cfg.range = BMA4_ACCEL_RANGE_2G;
      cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
      cfg.perf_mode = BMA4_CONTINUOUS_MODE;
      TTGOClass::getWatch()->bma->accelConfig(cfg);
      TTGOClass::getWatch()->bma->enableAccel();
      pinMode(BMA423_INT1, INPUT);
      attachInterrupt(
        BMA423_INT1,
        [] {},
        RISING
      ); //It must be a rising edge
      TTGOClass::getWatch()->bma->enableFeature(BMA423_STEP_CNTR, true);
      TTGOClass::getWatch()->bma->enableStepCountInterrupt();
    }

    void _handleBatteryIRQ() {
      if (BatteryManager::getInstance()->handleCabelPlugIRQ()) {
        TTGOClass::getWatch()->motor->onec();
        InactivityWatcher::getInstance()->markActivity();
      }
    }
    
};

CyberWatch* CyberWatch::_inst;
