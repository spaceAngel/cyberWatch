#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/App.h"

class StopWatch : public App {
	public:

		void render();
		bool handlePEKShort();
		bool isSystemSleepForbidden();

		bool controlModeIsTouch() {
			return true;
		}

		bool handleTouch(uint8_t x, uint8_t y);


		StopWatch() {}

		protected:

			const uint8_t POS_Y = 83;

			int64_t prevTime;
			uint8_t prevHour = 0;
			uint8_t prevSecond = 0;
			uint8_t prevMinute = 0;

			void renderTime(int64_t stopTime);
			void renderHour(uint8_t hour);
			void renderSeconds(uint8_t seconds);
			void renderMinutes(uint8_t minutes);
			void renderMillis(uint8_t millis);

};
