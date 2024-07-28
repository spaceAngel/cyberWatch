#pragma once

#include "Apps/WatchFaces/WatchFace.h"

class SensorGrid : public WatchFace {

	public:

		void render();

		SensorGrid();

		bool hasInfoPanel() {
			return true;
		}

	protected:
		uint8_t prevMinute = 99;
		uint8_t prevSecond = 99;

		uint32_t colors[5] = {TFT_DARKGREEN, TFT_GREEN, TFT_GREENYELLOW, TFT_RED, TFT_ORANGE};

		void renderTime();

		void renderSensorGrid();

		void renderSensorGridCell(uint8_t line);

		uint8_t getCellCount();

};
