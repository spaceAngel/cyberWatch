#pragma once

#include "../../System/MotorController.cpp"
#include "Components/Logo.cpp"

class SplashScreen {

  public:

    void show() {
      MotorController::vibrate();
      
      Logo *logo = new Logo();
      logo->render();
      _renderLoadingBar();
      _resetToDefault();
      MotorController::vibrate();
      delay(200);
    }

  protected:

    void _resetToDefault() {
      TTGOClass::getWatch()->tft->setTextFont(4); //reset to default
      TTGOClass::getWatch()->tft->setTextSize(1); //reset to default
      //clear display
      TTGOClass::getWatch()->tft->fillRect( 
        0,
        0,
        TTGOClass::getWatch()->tft->width(),
        TTGOClass::getWatch()->tft->height(),
        TFT_BLACK
      );
    }

    void _renderLoadingBar() {
      uint margin = 20;
      //"loading effect" progressbar
      for (uint i = margin; i < TTGOClass::getWatch()->tft->width() - margin * 2; i++) {
        TTGOClass::getWatch()->tft->fillRect(
          margin, 
          TTGOClass::getWatch()->tft->height() - 60,
          i, 
          10,
          TFT_DARKGREEN
        );
        delay(25);
      }
    }

   
};
