#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/Component.h"

class Date : public Component {
	public:
		void render();

		protected:

			const int32_t POS_Y = 18;

			uint8_t prevDay = 99;

			void renderDate(RTC_Date currentDate);
			void renderDayInWeek(RTC_Date currentDate);

};
