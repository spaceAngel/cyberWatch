#include "IconConverter.h"

#include <Arduino.h>
#include "config.h"
#include "UserInterface/Icons/IconStruct.h"

IconStruct IconConverter::convertIcon(
	IconStruct original,
	uint32_t fgColor,
	uint32_t bgColor
) {
	IconStruct rslt;
	unsigned short rsltData[1024] = {};
	for (uint16_t i = 0; i < 1024; i++) {
		if (original.data[i] == 0x07e0) {
			rslt.data[i] = fgColor;
		} else if(original.data[i] == 0x0000) {
			rslt.data[i] = bgColor;
		} else {
			rslt.data[i] = original.data[i];
		}
	}


	rslt.width = original.width;
	rslt.heigth = original.heigth;

	return rslt;

}