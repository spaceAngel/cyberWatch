#pragma once

#include <Arduino.h>

#include "AlarmModel.h"

class AlarmStorage {

	public:

		AlarmModel *getAlarm(uint8_t alarm);

		static AlarmStorage *getInstance();

		uint8_t getAlarmsCount() {return 3;};

	protected:

		static AlarmStorage *inst;

		AlarmModel *alarms[3];


		AlarmStorage() {
			this->alarms[0] = new AlarmModel();
			this->alarms[1] = new AlarmModel();
			this->alarms[2] = new AlarmModel();

		}



};
