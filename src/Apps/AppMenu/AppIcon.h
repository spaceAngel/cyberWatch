#pragma once

#include <Arduino.h>

struct AppIcon {
	uint8_t width;
	uint8_t heigth;
	uint16_t data[16 * 144];
};
