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
        TTGOClass::getWatch()->tft->setTextSize(3);
        TTGOClass::getWatch()->tft->fillRect(
          0,
          POS_Y,
          TTGOClass::getWatch()->tft->width(),
          TTGOClass::getWatch()->tft->fontHeight() + 1,
          TFT_BLACK
        );

        TTGOClass::getWatch()->tft->drawString(
          timeStr,
          (TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(timeStr)) / 2,
          POS_Y + 3
        );
        TTGOClass::getWatch()->tft->setTextSize(1); // reset size to default
        _prevMinute = currentTime.minute;
      }
    }

    void rerender() {
    } 

  protected:
    uint _prevMinute = 99;
    const uint POS_Y = 62;

};
