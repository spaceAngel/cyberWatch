#pragma once

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
      return _lastActivity + INACTIVITY_TRESHOLD < millis();
    }

    void markActivity() {
      _lastActivity = millis();
    }

    protected:

      static InactivityWatcher *_inst;

      const long INACTIVITY_TRESHOLD = 5000;

      long _lastActivity;

      InactivityWatcher() {
        _lastActivity = millis();
      }

};

InactivityWatcher* InactivityWatcher::_inst;
