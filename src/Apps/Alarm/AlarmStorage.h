#pragma once

#include <Arduino.h>

#include "AlarmModel.h"

class AlarmStorage {

	public:

		AlarmModel *getAlarm(uint8_t alarm);

		static AlarmStorage *getInstance();

		uint8_t getAlarmsCount() {return 3;};

		bool isActiveAlarm();

		void save();
		void load();

	protected:

		const char *FILENAME = "/alarms.dat";
		static AlarmStorage *inst;

		AlarmModel *alarms[3];


		AlarmStorage();
};
