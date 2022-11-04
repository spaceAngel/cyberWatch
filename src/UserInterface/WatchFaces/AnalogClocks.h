#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/WatchFaces/WatchFace.h"

class AnalogClocks : public WatchFace {

	public:

		void render();

		bool hasToolbar() {
			return true;
		}

	protected:

		uint8_t prevSecond = 99;

		void drawLine(int32_t time, uint8_t radius, uint32_t color);
		void clear();
		void renderFace();

};
