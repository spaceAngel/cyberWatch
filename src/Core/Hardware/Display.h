#pragma once

#include "Utils/TimeUtil.h"

#define ADJUST_MIN 5
#define ADJUST_MAX 250

class Display {

	public:

		static Display *getInstance();

		void init();

		bool isDisplayOn();

		void turnDisplayOff();

		void turnDisplayOn();

		uint8_t getAdjust();

		void setAdjust(uint8_t adjustPercent);

		void resetTypographySettings();

		protected:

			static Display *inst;

			uint lastOn = TimeUtil::getCurrentTimeInSeconds();

			uint8_t adjustPercent;

			Display() {
			}

};
