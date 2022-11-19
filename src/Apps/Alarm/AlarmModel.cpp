#include "AlarmModel.h"

void AlarmModel::setEnabled(bool enabled) {
	this->enabled = enabled;
	if (this->enabled == false) {
		this->minute = 0;
		this->hour = 0;
		for (uint8_t i = 0; i < 7; i++) {
			this->days[i] = false;
		}
	}
}

bool AlarmModel::isRunningOnce() {
	bool rslt = true;
	for (uint8_t i = 0; i < 7; i++) {
		if (this->days[i] == true) {
			rslt = false;
		}
	}
	return rslt;
}

void AlarmModel::setIsRunningOnce() {
	for (uint8_t i = 0; i < 7; i++) {
		this->days[i] = false;
	}
}
