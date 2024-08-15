#pragma once

#include <Arduino.h>
#include "UserInterface/Icons/IconStruct.h"

class IconConverter {

	public:

		static IconStruct convertIcon(IconStruct original, uint32_t fgColor, uint32_t bgColor);


};
