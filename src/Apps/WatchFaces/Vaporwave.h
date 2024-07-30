#pragma once

#include "Apps/WatchFaces/WatchFace.h"

class Vaporwave : public WatchFace {

	public:

		void render();

		Vaporwave() {}

		bool hasInfoPanel() {
			return false;
		}

	protected:
		uint8_t prevMinute = 99;

		void renderTime();
		void renderDate();

};
