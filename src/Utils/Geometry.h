#pragma once

#include "config.h"
#include <LilyGoWatch.h>

class Geometry {

	public:

		static void calculatePointOnCircle(
			uint8_t x,
			uint8_t y,
			int16_t angle,
			uint8_t radius,
			int32_t &x1,
			int32_t &y1
		);

};
