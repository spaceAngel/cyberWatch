#pragma once

#include <Arduino.h>
#include "UserInterface/App.h"

class AlarmRinging : public App {

	public:
		void render();

		bool hasNotificationBar() {return true;}
		bool controlModeIsTouch() {return true;}
		bool canHandleLongTouch() {return true;}
		bool canBeTouchedLocked() {return true;}

		bool handleLongTouch(uint8_t x, uint8_t y);

		AlarmRinging(uint8_t alarmHour, uint8_t alarmMinute);

	protected:

		uint64_t lastVibrationTime = 0;
		uint8_t alarmHour;
		uint8_t alarmMinute;

		void renderMsgBox();
};
