#include "AppSettings.h"
#include "Core/Registry.h"

AppSettings *AppSettings::inst;

AppSettings::AppSettings() {
	uint value = Registry::getInstance()->getValue(REGISTRY_SETTINGS, 0);
	this->bits = value;
}

AppSettings *AppSettings::getInstance() {
	if (AppSettings::inst == nullptr) {
		AppSettings::inst = new AppSettings();
	}
	return AppSettings::inst;
}

uint8_t AppSettings::getSettingsByteMask() {
	return this->bits;
}

void AppSettings::set(uint8_t bit, bool value) {
	if (value == true) {
		this->bits |= bit;
	} else {
		this->bits &= ~bit;
	}
	Registry::getInstance()->setValue(
		REGISTRY_SETTINGS,
		this->bits
	);
}

void AppSettings::toggle(uint8_t bit) {
	this->set(
		bit,
		!this->get(bit)
	);
}

bool AppSettings::get(uint8_t bit) {
	return (this->bits & bit) == bit;
}
