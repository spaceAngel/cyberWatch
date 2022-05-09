#pragma once

#include "Display/Display.cpp"
#include "System/InactivityWatcher.cpp"
#include "System/Esp32.cpp"
#include "System/MotorController.cpp"
#include <LilyGoWatch.h>

#define TICK_SLEEP 200
#define TICK_WAKEUP 10

#include "../config.h"

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
         
      BatteryManager::getInstance()->energyConsumptionSavingsSettings();
      Esp32::getInstance()->initIRQ();
      _initStepCounter();
      Display::getInstance()->showSplashScreen();
    };

    void loop() {
      int16_t x, y;

      while(1) {
        bool PEKshort = false;

        _handleBatteryLowActions();

        if (Esp32::getInstance()->isIRQ()) {
          TTGOClass::getWatch()->power->readIRQ();
          _handleEsp32IRQ();
          if(TTGOClass::getWatch()->power->isPEKShortPressIRQ()) {
            PEKshort = true;
          }
          Esp32::getInstance()->cleanIRQ();
        }

        if (
          (
            TTGOClass::getWatch()->getTouch(x, y)
            && (x != 257 && y != 2) //some kind of HW error in my LILLYGO T-Watch (short circuit?)
          )
          || PEKshort
        ) {
          InactivityWatcher::getInstance()->markActivity();
        }
        if (InactivityWatcher::getInstance()->isInactive()) {
          Display::getInstance()->turnDisplayOff();
          esp_sleep_enable_timer_wakeup(TICK_SLEEP); 
          esp_light_sleep_start();
        } else {
          if (!Display::getInstance()->isDisplayOn()) {
            Display::getInstance()->turnDisplayOn();
          }
          Display::getInstance()->render();
          delay(TICK_WAKEUP);
        }
      }
    };

  protected:
    static CyberWatch *_inst;

    CyberWatch() {
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

    void _handleCabelConnection() {
      if (BatteryManager::getInstance()->handleCabelPlugIRQ()) {
        TTGOClass::getWatch()->motor->onec();
        InactivityWatcher::getInstance()->markActivity();
      }
    }

    void _handleEsp32IRQ() {
      if (BatteryManager::getInstance()->handleCabelPlugIRQ()) {
        _handleCabelConnection();
      }
    }

    uint8_t _batteryLowWarnVibrateOnLevel = 101;

    void _handleBatteryLowActions() {
      uint8_t vibrationCount = 0;
      uint8_t capacity = BatteryManager::getInstance()->getCapacity();
      if (BatteryManager::getInstance()->isCharging()) {
        _batteryLowWarnVibrateOnLevel = 101;
        return;
      }
      if (capacity == BATTERY_LOW) {
        vibrationCount = 1;
      }

      if (capacity == BATTERY_VERY_LOW) {
        vibrationCount = 2;
      }

      if (
        vibrationCount > 0
        && capacity < _batteryLowWarnVibrateOnLevel
      ) {
        InactivityWatcher::getInstance()->markActivity();
        MotorController::vibrate(vibrationCount);
        _batteryLowWarnVibrateOnLevel = capacity;
      }
    }
    
};

CyberWatch* CyberWatch::_inst;
