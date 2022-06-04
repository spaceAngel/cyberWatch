#pragma once

#include <Arduino.h>


struct IconStruct {
	uint8_t width;
	uint8_t heigth;
	unsigned short data[1024];
};
