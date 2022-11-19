#pragma once

#include <Arduino.h>

class AlarmModel {

	public:
		uint8_t getHour() {return this->hour;}
		uint8_t getMinute() {return this->minute;}

		void setHour(uint8_t hour) {this->hour = hour;}
		void setMinute(uint8_t minute) {this->minute = minute;}

		bool getIsEnabledForDay(uint8_t day) {return this->days[day];}
		void setIsEnabledForDay(uint8_t day, bool value) {this->days[day] = value;}

		void setEnabled(bool enabled);
		bool getEnabled() {return this->enabled;}

		bool isRunningOnce();
		void setIsRunningOnce();

		AlarmModel() {};

	protected:

		uint8_t hour = 0;
		uint8_t minute = 0;

		bool enabled = false;

		bool days[7] = {false, false, false, false, false, false, false};
};
