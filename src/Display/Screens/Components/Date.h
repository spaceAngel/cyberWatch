#pragma once

#include "config.h"

#include <LilyGoWatch.h>

class Date {
	public:
		void render();

		protected:

			const uint POS_Y = 18;

			uint _prevDay = 99;

			void _renderDate(RTC_Date currentDate);
			void _renderDayInWeek(RTC_Date currentDate);
			void _weekday(char *dayInWeekStr, int year, int month, int day);

};
