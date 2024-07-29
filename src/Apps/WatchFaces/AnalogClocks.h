#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "Apps/WatchFaces/WatchFace.h"

class AnalogClocks : public WatchFace {

	public:

		void render();

		bool hasToolbar() {
			return false;
		}

		bool runWithHighSpeed() {
			return true;
		}

	protected:

		uint8_t prevMinute = 99;

		uint8_t const POS_Y = 136;
		uint8_t const RADIUS = 95;

		void drawLine(int32_t time, uint8_t radius, uint32_t color);
		void clear();
		void renderFace();
		void renderDate(RTC_Date date);

};
