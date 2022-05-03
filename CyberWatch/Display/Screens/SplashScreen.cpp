#pragma once

class SplashScreen {

  public:

    void show() {
      TTGOClass::getWatch()->motor->onec();
      
      _renderLogo();
      _renderLoadingBar();

      _resetToDefault();
      TTGOClass::getWatch()->motor->onec();
      delay(200);
      TTGOClass::getWatch()->tft->setTextFont(4); //reset to default
      TTGOClass::getWatch()->tft->setTextSize(1); //reset to default
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

    void _renderLogo() {
      TTGOClass::getWatch()->tft->setTextFont(2);
      TTGOClass::getWatch()->tft->setTextSize(3);

      TTGOClass::getWatch()->tft->drawString(
        APP_NAME,
        (TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(APP_NAME)) / 2,
        TTGOClass::getWatch()->tft->height() / 2 - TTGOClass::getWatch()->tft->fontHeight()
      );

      TTGOClass::getWatch()->tft->setTextSize(2);
      TTGOClass::getWatch()->tft->drawString(
        APP_VERSION,
        (TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(APP_VERSION)) / 2,
        TTGOClass::getWatch()->tft->height() / 2
      );
    }
};
