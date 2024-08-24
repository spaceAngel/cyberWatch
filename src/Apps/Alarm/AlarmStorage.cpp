#include "AlarmStorage.h"
#include "AlarmModel.h"

#include "Core/Hardware/MotorController.h"
#include "config.h"
#include <LilyGoWatch.h>
#include "UserInterface/Screens/MainScreen.h"

#include "Core/Registry.h"
#include "Core/Hardware/MotorController.h"

using namespace std;

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

void AlarmStorage::save() {
	char save[100];
	uint8_t data[30] = {};

	for (uint8_t i = 0; i < 3; i++) {
		uint8_t shift = i * 10;
		data[shift] = this->getAlarm(i)->getEnabled() ? 1 : 0;
		for (int j = 0; j < 7; j++) {
			data[shift + 1+ j] = this->getAlarm(i)->getIsEnabledForDay(j);
		}
		data[shift + 8] = this->getAlarm(i)->getHour();
		data[shift + 9] = this->getAlarm(i)->getMinute();

	}
	Registry::getInstance()->setValue(REGISTRY_ALARM, data, 30);

}

void AlarmStorage::load() {
	char buffer[30];  // prepare a buffer for the data
  	Registry::getInstance()->getBytes(REGISTRY_ALARM, buffer, 30);
  	alarm_t *alarms = (alarm_t *)buffer;  // cast the bytes into a struct ptr
	for (uint8_t i = 0; i< 3; i++) {

		if (alarms[i].enabled == 1)  {
			this->getAlarm(i)->setEnabled(true);
			this->getAlarm(i)->setIsEnabledForDay(0, alarms[i].enabledMo);
			this->getAlarm(i)->setIsEnabledForDay(1, alarms[i].enabledTu);
			this->getAlarm(i)->setIsEnabledForDay(2, alarms[i].enabledWe);
			this->getAlarm(i)->setIsEnabledForDay(3, alarms[i].enabledTh);
			this->getAlarm(i)->setIsEnabledForDay(4, alarms[i].enabledFr);
			this->getAlarm(i)->setIsEnabledForDay(5, alarms[i].enabledSa);
			this->getAlarm(i)->setIsEnabledForDay(6, alarms[i].enabledSu);
			this->getAlarm(i)->setHour(alarms[i].hour);
			this->getAlarm(i)->setMinute(alarms[i].minute);
		}
	}
}

AlarmStorage::AlarmStorage() {
	this->alarms[0] = new AlarmModel();
	this->alarms[1] = new AlarmModel();
	this->alarms[2] = new AlarmModel();
	this->load();
}







