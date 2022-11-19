#include "AlarmStorage.h"
#include "AlarmModel.h"

AlarmStorage *AlarmStorage::inst;

AlarmStorage *AlarmStorage::getInstance() {
	if (AlarmStorage::inst == nullptr) {
		AlarmStorage::inst = new AlarmStorage();
	}
	return AlarmStorage::inst;
}

AlarmModel *AlarmStorage::getAlarm(uint8_t alarm) {
	return this->alarms[alarm];
}
