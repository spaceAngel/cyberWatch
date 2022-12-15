#include "AlarmStorage.h"
#include "AlarmModel.h"

#include <SPIFFS.h>
#include <FS.h>
#include <string.h>
#include "Core/Hardware/MotorController.h"
#include "config.h"
#include <LilyGoWatch.h>
#include "UserInterface/Screens/MainScreen.h"
#include <string>
#include <iostream>
#include <sstream>

#include "Utils/StringUtils.h"

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
	fs::File file = SPIFFS.open(AlarmStorage::FILENAME, FILE_WRITE);
	char save[100];
	for (uint8_t i = 0; i < 3; i++) {

		strcat(save, "A");
		strcat(save, this->getAlarm(i)->getEnabled() ? "Y" : "N");
		strcat(save, "E");
		for (int j = 0; j < 7; j++) {
			strcat(save,  this->getAlarm(i)->getIsEnabledForDay(j) ? "Y" : "N");
		}
		strcat(save, "W");
		char hours[3];
		(void)snprintf(hours, sizeof(hours), "%02d", this->getAlarm(i)->getHour());
		strcat(save, hours);
		strcat(save, "H");

		char minutes[3];
		(void)snprintf(minutes, sizeof(minutes), "%02d", this->getAlarm(i)->getMinute());
		strcat(save, minutes);
		strcat(save, "M");

	}
	file.print(save);
	file.close();

}

void AlarmStorage::load() {
	fs::File file = SPIFFS.open(AlarmStorage::FILENAME, FILE_READ);
	String fromFile;
	String a = "Y";
	for (uint8_t i = 0; i< 3; i++) {
		file.readStringUntil('A');
		String enabled = file.readStringUntil('E');
		if (enabled.substring(0, 1) == a)  {
			this->getAlarm(i)->setEnabled(true);
			String weekdays = file.readStringUntil('W');
			for (uint8_t j = 0; j < 7; j++) {
				if (weekdays.substring(j, j + 1) == a) {
					this->getAlarm(i)->setIsEnabledForDay(j, true);
				}
			}

			this->getAlarm(i)->setHour(
				StringUtils::stringToUint(file.readStringUntil('H'))
			);
			this->getAlarm(i)->setMinute(
				StringUtils::stringToUint(file.readStringUntil('M'))
			);
		}
	}
	file.close();
}

AlarmStorage::AlarmStorage() {
	this->alarms[0] = new AlarmModel();
	this->alarms[1] = new AlarmModel();
	this->alarms[2] = new AlarmModel();
	this->load();
}







