#pragma once

#include <LilyGoWatch.h>

class Date {
  public:
    void render() {
      RTC_Date currentDate = TTGOClass::getWatch()->rtc->getDateTime();
      char dateStr[11];
      snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%02d", currentDate.day, currentDate.month, currentDate.year);       
      if (
        _prevDay != currentDate.day
      ) {
        TTGOClass::getWatch()->tft->fillRect(
          0,
          POS_Y,
          TTGOClass::getWatch()->tft->width(),
          TTGOClass::getWatch()->tft->fontHeight() + 1,
          TFT_BLACK
        );

        TTGOClass::getWatch()->tft->drawString(
          dateStr,
          (TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(dateStr)) / 2,
          POS_Y + 3
        );
        _prevDay = currentDate.day;
      }
    }

    void rerender() {
    } 

    protected:
    
      const uint POS_Y = 32;

      uint _prevDay = 99;

};
