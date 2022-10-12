#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class AboutPanel : public MainComponent {
	public:

		void render();

		AboutPanel();

	protected:

		uint8_t prevSecond = 0;

		uint8_t calculatePosY(uint8_t row, bool shifted);

};
