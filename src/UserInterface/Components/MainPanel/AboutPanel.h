#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class AboutPanel : public MainComponent {
	public:

		void render();

		AboutPanel();

	protected:

		uint prevUptime = 0;

		uint8_t calculatePosY(uint8_t row, bool shifted);

		void secondsToString(uint totalSeconds, char (&string)[20]);

		void renderCompilationData();

		void renderDateDiff(uint seconds, uint8_t row);

};
