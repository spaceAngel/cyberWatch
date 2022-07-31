#include "config.h"

#include <Arduino.h>
#include <LilyGoWatch.h>

#include "MotorController.h"

void MotorController::vibrate(uint8_t count) {
	#ifdef LILYGO_WATCH_HAS_MOTOR
		TTGOClass::getWatch()->motor->onec(100);
		for (uint8_t i = 1; i < count; i++) {
			delay(350);
			TTGOClass::getWatch()->motor->onec(150);
		}
	#endif
}
