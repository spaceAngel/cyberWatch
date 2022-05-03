#pragma once

#include "Components/Time.cpp"
#include "Components/Date.cpp"
#include "Components/InfoPanel/InfoPanel.cpp"

#include <LilyGoWatch.h>

class DefaultScreen {

  public:

    static DefaultScreen *getInstance()
    {
        if (DefaultScreen::_inst == nullptr) {
            DefaultScreen::_inst = new DefaultScreen();
        }
        return DefaultScreen::_inst;
    }

    void render() {
      TTGOClass::getWatch()->tft->drawString(APP_FULL_NAME, 30, 18);
      _time->render();
      _date->render();
      _infoPanel->render();
    }

    void rerender() {      
    }

    protected:

      static DefaultScreen *_inst;

      Time *_time;
      Date *_date;
      InfoPanel *_infoPanel;

      DefaultScreen() {
        _time = new Time();
        _date = new Date();
        _infoPanel = new InfoPanel();
      }
};

DefaultScreen* DefaultScreen::_inst;
