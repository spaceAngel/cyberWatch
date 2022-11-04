#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class AnalogClocks : public MainComponent {

	public:

		void render();

	protected:

		uint8_t prevSecond = 99;

		void drawLine(int32_t time, uint8_t radius, uint32_t color);
		void clear();
		void renderFace();

};
