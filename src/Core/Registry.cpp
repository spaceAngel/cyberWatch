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

size_t Registry::getBytes(const char* key, void * buf, size_t maxLen) {
	return this->preferences.getBytes(key, buf, maxLen);
}


void Registry::setValue(const char* key, uint value) {
	this->preferences.putUInt(key, value);
}

void Registry::setValue(const char* key, const void* value, uint8_t size) {
	  this->preferences.putBytes(key, value, size);
}
