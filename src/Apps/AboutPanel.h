#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/App.h"

class AboutPanel : public App {
	public:

		void render();

		AboutPanel();

		bool handlePEKShort();

	protected:

		uint prevUptime = 0;

		uint8_t calculatePosY(uint8_t row, bool shifted);

		void secondsToString(uint totalSeconds, char (&string)[20]);

		void renderCompilationData();

		void renderDateDiff(uint seconds, uint8_t row);

};
