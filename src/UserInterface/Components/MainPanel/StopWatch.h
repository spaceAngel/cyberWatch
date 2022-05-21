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

		protected:

			const uint8_t POS_Y = 48;

			uint64_t _startAt = 0;
			uint64_t _stopAt = 0;
			uint64_t _prevTime;
			bool _isRunning = false;

			void _renderTime(long stopTime);

};
