#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"

class Calendar : public MainComponent {

	public:

		bool handleVerticalSwipe(int8_t vector);
		bool handlePEKShort();
		void prevMonth();
		void nextMonth();
		void setYearMonth(uint16_t year, uint8_t month);
		void render();
		Calendar();

	protected:

		uint8_t day;
		uint8_t month;
		uint16_t year;

		void renderDay(uint8_t day, uint8_t row, uint8_t dayInWeek);
		void renderDelimiter(uint8_t day, uint8_t row, uint8_t dayInWeek);
		void renderIsNowBox(uint8_t day, uint8_t row, uint8_t dayInWeek);
		void renderMonthYearLabel();

};
