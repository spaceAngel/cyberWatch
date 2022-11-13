#include "MathUtil.h"

uint MathUtil::getRandomUint8(uint8_t maxValue)  {
	uint8_t rslt;
	while( (rslt = rand()) > maxValue )  {}
	return rslt;

}


