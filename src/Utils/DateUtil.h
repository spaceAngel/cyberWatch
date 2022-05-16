#pragma once

#include "config.h"

#include <Arduino.h>

class DateUtil {

	public:

		static uint8_t weekday(uint year, uint8_t month, uint8_t day);

};
