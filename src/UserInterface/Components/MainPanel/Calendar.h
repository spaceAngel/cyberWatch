#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"

class Calendar : public MainComponent {

	public:

		bool handleVerticalSwipe(int8_t vector);
		void prevMonth();
		void nextMonth();
		void setYearMonth(uint16_t year, uint8_t month);
		void render();
		Calendar();

	protected:

		uint8_t _day;
		uint8_t _month;
		uint16_t _year;

		void _renderDay(uint8_t day, uint8_t row, uint8_t dayInWeek);
		void _renderDelimiter(uint8_t day, uint8_t row, uint8_t dayInWeek);
		void _renderIsNowBox(uint8_t day, uint8_t row, uint8_t dayInWeek);
		void _renderMonthYearLabel();

};
