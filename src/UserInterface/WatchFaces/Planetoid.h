#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/WatchFaces/WatchFace.h"

class Planetoid : public WatchFace {

	public:

		void render();

	protected:

		uint8_t prevSecond = 99;

		void clear();
		void renderFace();
		void renderPoint(uint16_t angle, uint8_t radius, uint8_t size, int color);

};
