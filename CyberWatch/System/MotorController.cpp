#pragma once

class MotorController {

  public:

    static void vibrate(uint8_t count = 1) {
      TTGOClass::getWatch()->motor->onec(100);
      for (uint8_t i = 1; i < count; i++) {
        delay(350);
        TTGOClass::getWatch()->motor->onec(150);
      }
    }

};
