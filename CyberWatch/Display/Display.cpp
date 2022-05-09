#pragma once

#include <LilyGoWatch.h>
#include "Screens/MainScreen.cpp"
#include "Screens/SplashScreen.cpp"
#include "Screens/ExitScreen.cpp"
#include "../Utils/TimeUtil.cpp"
#include "../../config.h"

class Display {

  public:

    static Display *getInstance()
    {
        if (Display::_inst == nullptr) {
            Display::_inst = new Display();
        }
        return Display::_inst;
    }

    void showSplashScreen() {
      SplashScreen *screen = new SplashScreen();
      screen->show();
    }

    void showExitScreen() {
      ExitScreen *screen = new ExitScreen();
      screen->show();
    }

    void init() {
      TTGOClass::getWatch()->openBL();
      TTGOClass::getWatch()->bl->adjust(DISPLAY_ADJUST);
      TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
    }

    void render() {
      MainScreen::getInstance()->render();
    }

    bool isDisplayOn() {
      return _lastOn > 0;
    }

    void turnDisplayOff() {

      if (isDisplayOn()) {
        TTGOClass::getWatch()->displaySleep();
        TTGOClass::getWatch()->bl->off();
        _lastOn = 0;
      }
    }

    void turnDisplayOn() {
      if (!isDisplayOn()) {
        render();
        TTGOClass::getWatch()->bl->on();
        TTGOClass::getWatch()->displayWakeup();
        _lastOn = TimeUtil::getCurrentTimeInSeconds();
      }
    }

    protected:

      static Display *_inst;

      uint _lastOn = TimeUtil::getCurrentTimeInSeconds();

      Display() {
      }

};

Display* Display::_inst;
