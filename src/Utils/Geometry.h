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
			uint8_t &x1,
			uint8_t &y1
		);

};
