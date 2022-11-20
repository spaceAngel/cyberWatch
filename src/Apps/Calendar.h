#pragma once

#include <Arduino.h>

#include "UserInterface/App.h"

class Calendar : public App {

	public:

		bool handleSwipeVertical(int8_t vector);
		bool canHandleLongTouch() {return true;};

		bool handleLongTouch(uint8_t x, uint8_t y);

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
