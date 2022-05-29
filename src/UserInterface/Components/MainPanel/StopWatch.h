#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class StopWatch : public MainComponent {
	public:

		void render();
		bool handlePEKShort();
		bool handleVerticalSwipe(int8_t vector) {return false;}
		bool isRunning();

		StopWatch();

		protected:

			const uint8_t POS_Y = 48;

			uint64_t startAt = 0;
			uint64_t stopAt = 0;
			uint64_t prevTime;
			bool running = false;
			uint8_t prevHour = 0;
			uint8_t prevSecond = 0;
			uint8_t prevMinute = 0;

			void renderTime(long stopTime);
			void renderHour(uint8_t hour);
			void renderSeconds(uint8_t seconds);
			void renderMinutes(uint8_t minutes);
			void renderMillis(uint8_t millis);

};
