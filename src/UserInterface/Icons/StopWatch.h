#pragma once

#include <pgmspace.h>
#include <Arduino.h>
#include "IconStruct.h"

const IconStruct iconStopWatch PROGMEM = {
	22,
	22,
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0340, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x03a0, 0x0000,
		0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000,
		0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000,
		0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0780, 0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x0000, 0x0180,
		0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000,
		0x0000, 0x0000, 0x07e0, 0x07e0, 0x0000, 0x0180, 0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0180, 0x07e0, 0x0000, 0x0000, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0,
		0x0000, 0x0180, 0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000,
		0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x07c0, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000,
		0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0040, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07e0, 0x07e0, 0x07e0,
		0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01a0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x07e0, 0x01e0, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000
	}
};
