#include "config.h"

#include "Registry.h"

#include <Preferences.h>


Registry* Registry::inst;

Registry *Registry::getInstance() {

	if (Registry::inst == nullptr) {
		Registry::inst = new Registry();
	}
	return Registry::inst;
}

Registry::Registry() {
	this->preferences.begin(APP_NAME, false);
}

uint Registry::getValue(const char* key, uint defaultValue) {
	if (this->preferences.isKey(key)) {
		return this->preferences.getUInt(key);
	}
	return defaultValue;
}

void Registry::setValue(const char* key, uint value) {
	this->preferences.putUInt(key, value);
}
