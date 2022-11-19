#pragma once

#include "UserInterface/App.h"

#include <Arduino.h>

#include "Alarm/Components/AlarmDisplay.h"

class Alarm : public App {

	public:

		void render();

		Alarm();

		bool canHandleLongTouch() {
			return true;
		}

		bool handleLongTouch(uint8_t x, uint8_t y);

		void setShouldReRender(bool shouldReRender);

	protected:

		AlarmDisplay *alarms[3];

		const uint8_t ALARM_SLOTS = 2;

		void renderAlarm(uint8_t line);

};
