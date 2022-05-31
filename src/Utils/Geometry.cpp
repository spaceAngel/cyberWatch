#include "Geometry.h"

#include "config.h"
#include <math.h>
#include <LilyGoWatch.h>

int32_t Geometry::getCalculatedXPointOnCircle(
	uint8_t x,
	int16_t angle,
	uint8_t radius
) {
	int16_t derivatedAngle = angle - (int16_t)90;
	float a = derivatedAngle * (M_PI / 180);
	return x + (cos(a) * radius);
}

uint32_t Geometry::getCalculatedYPointOnCircle(
	uint8_t y,
	int16_t angle,
	uint8_t radius
) {
	int16_t derivatedAngle = angle - (int16_t)90;
	float a = derivatedAngle * (M_PI / 180);
    return y + (sin(a) * radius);
}
