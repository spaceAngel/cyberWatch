#include "StringUtils.h"

#include <Arduino.h>
#include <string>

uint StringUtils::stringToUint(String input) {
	uint rslt = 0;
	for (uint8_t i = 0; i < input.length(); i++) {
		rslt *= 10;
		rslt += (input.charAt(i) - 48);
	}
	return rslt;
}
