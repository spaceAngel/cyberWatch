#pragma once

#include "Utils/TimeUtil.h"

class Display {

	public:

		static Display *getInstance();

		void init();

		bool isDisplayOn();

		void turnDisplayOff();

		void turnDisplayOn();

		protected:

			static Display *inst;

			uint lastOn = TimeUtil::getCurrentTimeInSeconds();

			Display() {
			}

};
