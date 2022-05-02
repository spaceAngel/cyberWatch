#pragma once

#include <LilyGoWatch.h>

class Time {
  public:
    void render() {
      RTC_Date currentTime = TTGOClass::getWatch()->rtc->getDateTime();
     if (
        _prevMinute != currentTime.minute
      ) {
        char timeStr[6];
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentTime.hour, currentTime.minute);       
        TTGOClass::getWatch()->tft->setTextFont(6);
        TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
        TTGOClass::getWatch()->tft->fillRect(POS_X, POS_Y, 140, 48, TFT_BLACK);
        TTGOClass::getWatch()->tft->drawString(timeStr, POS_X + 10, POS_Y + 3);
        _prevMinute = currentTime.minute;
        Serial.print("Karel");
      }
    }

    void rerender() {
    } 

  protected:
    uint _prevMinute = 99;
    const uint POS_X = 45;
    const uint POS_Y = 54;

};
