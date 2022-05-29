#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class Date : public MainComponent {
	public:
		void render();

		protected:

			const uint8_t POS_Y = 18;

			uint8_t prevDay = 99;

			void renderDate(RTC_Date currentDate);
			void renderDayInWeek(RTC_Date currentDate);
			void weekday(char *dayInWeekStr, uint year, uint8_t month, uint8_t day);

};
