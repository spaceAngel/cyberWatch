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

			uint64_t _startAt = 0;
			uint64_t _stopAt = 0;
			uint64_t _prevTime;
			bool _isRunning = false;
			uint8_t _prevHour = 0;
			uint8_t _prevSecond = 0;
			uint8_t _prevMinute = 0;

			void _renderTime(long stopTime);
			void _renderHour(uint8_t hour);
			void _renderSeconds(uint8_t seconds);
			void _renderMinutes(uint8_t minutes);
			void _renderMillis(uint8_t millis);

};
