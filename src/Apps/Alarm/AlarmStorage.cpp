#include "AlarmStorage.h"
#include "AlarmModel.h"

AlarmStorage *AlarmStorage::inst;

AlarmStorage *AlarmStorage::getInstance() {
	if (AlarmStorage::inst == nullptr) {
		AlarmStorage::inst = new AlarmStorage();
	}
	return AlarmStorage::inst;
}

bool AlarmStorage::isActiveAlarm() {
	for (uint8_t i = 0; i < 3; i++) {
		if (this->alarms[i]->getEnabled()) {
			return true;
		}
	}
	return false;
}

AlarmModel *AlarmStorage::getAlarm(uint8_t alarm) {
	return this->alarms[alarm];
}
