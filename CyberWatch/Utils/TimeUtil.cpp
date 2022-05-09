#pragma once

class TimeUtil {

  public:

    static uint getCurrentTimeInSeconds() {
      RTC_Date cd = TTGOClass::getWatch()->rtc->getDateTime();
      return (((cd.year * 365 + cd.month * 31 + cd.day) * 24 + cd.hour) * 60 + cd.minute) * 60 + cd.second;
    }
};
