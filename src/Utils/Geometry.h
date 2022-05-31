#pragma once

#include "config.h"
#include <LilyGoWatch.h>

class Geometry {

	public:

		static int32_t getCalculatedXPointOnCircle(
			uint8_t x,
			int16_t angle,
			uint8_t radius
		);

		static uint32_t getCalculatedYPointOnCircle(
			uint8_t yPoint,
			int16_t angle,
			uint8_t radius
		);

};
