#include "config.h"

#include "Registry.h"

#include <EEPROM.h>


Registry* Registry::inst;

Registry *Registry::getInstance() {

	if (Registry::inst == nullptr) {
		Registry::inst = new Registry();
	}
	return Registry::inst;
}

Registry::Registry() {
	EEPROM.begin(2);
}

uint Registry::getValue(uint address) {
	return EEPROM.read(address);
}

void Registry::setValue(uint address, uint value) {
	EEPROM.write(address, value);
	EEPROM.commit();
}
