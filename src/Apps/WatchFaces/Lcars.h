#pragma once

#include "Apps/WatchFaces/WatchFace.h"

class Lcars : public WatchFace {

	public:

		void render();

		Lcars() {}

		bool hasInfoPanel() {
			return false;
		}

	protected:
		uint8_t prevMinute = 99;

		void renderTime();
		void renderDate();


};
