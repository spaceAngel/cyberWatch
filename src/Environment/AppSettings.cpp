#include "AppSettings.h"

AppSettings *AppSettings::inst;

AppSettings::AppSettings() {
}

AppSettings *AppSettings::getInstance() {
	if (AppSettings::inst == nullptr) {
		AppSettings::inst = new AppSettings();
	}
	return AppSettings::inst;
}

void AppSettings::setAlwaysOn(bool alwaysOn) {
	if (alwaysOn == true) {
		this->bits |= APPSETTINGS_ALWAYS_ON;
	} else {
		this->bits &= ~APPSETTINGS_ALWAYS_ON;
	}
}

bool AppSettings::getAlwaysOn() {
	return (this->bits & APPSETTINGS_ALWAYS_ON) == APPSETTINGS_ALWAYS_ON;
}
