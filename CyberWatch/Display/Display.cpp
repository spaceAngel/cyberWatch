#pragma once

#include <LilyGoWatch.h>
#include "Screens/MainScreen.cpp"
#include "Screens/SplashScreen.cpp"

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

    void init() {
      TTGOClass::getWatch()->openBL();
      TTGOClass::getWatch()->bl->adjust(100);
      TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
    }

    void render() {
      if (!isDisplayOn()) {
        return;
      }
      MainScreen::getInstance()->render();
    }

    bool isDisplayOn() {
      return _displayOn;
    }

    void turnDisplayOff() {
      TTGOClass::getWatch()->displaySleep();
      TTGOClass::getWatch()->bl->off();
      _displayOn = false;
    }

    void turnDisplayOn() {
      TTGOClass::getWatch()->bl->on();
      TTGOClass::getWatch()->displayWakeup();
      render();
      _displayOn = true;
    }

    protected:

      static Display *_inst;

      bool _displayOn = true;

      Display() {
      }
};

Display* Display::_inst;
