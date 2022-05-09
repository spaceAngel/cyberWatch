#pragma once

#include "../Utils/TimeUtil.cpp"

class InactivityWatcher {

  public:
  
    static InactivityWatcher *getInstance()
    {

        if (InactivityWatcher::_inst == nullptr) {
            InactivityWatcher::_inst = new InactivityWatcher();
        }
        return InactivityWatcher::_inst;
    }

    bool isInactive() {
      return _lastActivity + INACTIVITY_TRESHOLD < TimeUtil::getCurrentTimeInSeconds();
    }

    void markActivity() {
      _lastActivity = TimeUtil::getCurrentTimeInSeconds();
    }

    protected:

      static InactivityWatcher *_inst;

      const long INACTIVITY_TRESHOLD = 5;

      long _lastActivity;

      InactivityWatcher() {
        _lastActivity = TimeUtil::getCurrentTimeInSeconds();
      }

};

InactivityWatcher* InactivityWatcher::_inst;
