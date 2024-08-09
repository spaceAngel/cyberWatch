#pragma once

#include <Arduino.h>

struct WatchFaceImage {
	uint8_t width;
	uint8_t heigth;
	uint16_t data[240 * 240];
};
