#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/WatchFaces/WatchFace.h"

class Planetoid : public WatchFace {

	public:

		void render();

		bool hasToolbar() {
			return true;
		}

	protected:

		uint8_t prevSecond = 99;

		uint8_t const POS_Y = 120;
		uint8_t const RADIUS = 80;

		void clear();
		void renderFace();
		void renderPoint(uint16_t angle, uint8_t radius, uint8_t size, int color);

};
