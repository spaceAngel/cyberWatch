#pragma once

#include "config.h"
#include <LilyGoWatch.h>
#include "Apps/WatchFaces/WatchFace.h"


class Mosaic : public WatchFace {

	public:

		void render();

		Mosaic() {}

		bool hasInfoPanel() {
			return false;
		}

		virtual bool runWithHighSpeed() {
			return true;
		}

	protected:
		uint8_t prevMinute = 99;
		const uint16_t PARTS_MIN = 150;
		const uint16_t PARTS = 260;

		const uint8_t COLORS_COUNT = 12;
		uint32_t colors[12] = {
			TFT_DARKGREEN,
			TFT_SKYBLUE,
			TFT_DARKCYAN,
			TFT_GOLD,
			TFT_YELLOW,
			TFT_RED,
			TFT_GREEN,
			TFT_YELLOW,
			TFT_GREENYELLOW,
			TFT_VIOLET,
			TFT_MAGENTA,
			TFT_OLIVE
		};

		void renderTime();
		void renderDate();
		void renderBackground();

};
