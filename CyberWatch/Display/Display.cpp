#pragma once

#include <LilyGoWatch.h>
#include "Screens/DefaultScreen/DefaultScreen.cpp"

class Display {

  public:

    static Display *getInstance()
    {
        if (Display::_inst == nullptr) {
            Display::_inst = new Display();
        }
        return Display::_inst;
    }

    void showSplashscreen() {
    }

    void init() {
      TTGOClass *watches = TTGOClass::getWatch();
      watches->openBL();
      watches->bl->adjust(DISPLAY_ADJUST);
      _currentScreen = Display::SCREEN_DEFAULT;
    }

    void render() {
      if (!isDisplayOn()) {
        return;
      }
      if (_currentScreen == Display::SCREEN_DEFAULT) {
         DefaultScreen::getInstance()->render();
      }
    }

    bool isDisplayOn() {
      return _displayOn;
    }

    void turnDisplayOff() {
      TTGOClass::getWatch()->displaySleep();
      TTGOClass::getWatch()->bl->adjust(0);
      _displayOn = false;
    }

    void turnDisplayOn() {
      TTGOClass::getWatch()->bl->adjust(DISPLAY_ADJUST);
      TTGOClass::getWatch()->displayWakeup();
      render();
      _displayOn = true;
    }

    protected:

      static Display *_inst;

      const static uint SCREEN_DEFAULT = 11;

      const uint DISPLAY_ADJUST = 130;

      uint _currentScreen;

      bool _displayOn = true;

      Display() {
      }
};

Display* Display::_inst;
