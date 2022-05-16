#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class Date : public MainComponent {
	public:
		void render();

		protected:

			const uint8_t POS_Y = 18;

			uint8_t _prevDay = 99;

			void _renderDate(RTC_Date currentDate);
			void _renderDayInWeek(RTC_Date currentDate);
			void _weekday(char *dayInWeekStr, uint year, uint8_t month, uint8_t day);

};
