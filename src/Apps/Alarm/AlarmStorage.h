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


typedef struct {
	uint8_t enabled;
	uint8_t enabledMo;
	uint8_t enabledTu;
	uint8_t enabledWe;
	uint8_t enabledTh;
	uint8_t enabledFr;
	uint8_t enabledSa;
	uint8_t enabledSu;
	uint8_t hour;
	uint8_t minute;
} alarm_t;