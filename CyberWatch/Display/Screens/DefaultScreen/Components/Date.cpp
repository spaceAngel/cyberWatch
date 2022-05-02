#pragma once

#include <LilyGoWatch.h>

class Date {
  public:
    void render() {
      RTC_Date cas = TTGOClass::getWatch()->rtc->getDateTime();
      char dateStr[11];
      snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%02d", cas.day, cas.month, cas.year);       
      if (
        _prevDay != cas.day
      ) {
        TTGOClass::getWatch()->tft->setTextFont(4);
        TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREEN);
        TTGOClass::getWatch()->tft->fillRect(45, POS_Y, 140, 28, TFT_BLACK);
        TTGOClass::getWatch()->tft->drawString(dateStr, POS_X + 10, POS_Y + 3);
        _prevDay = cas.day;
      }
    }

    void rerender() {
    } 

    protected:
    
      const uint POS_X = 45;
      const uint POS_Y = 100;

      uint _prevDay = 99;

};
