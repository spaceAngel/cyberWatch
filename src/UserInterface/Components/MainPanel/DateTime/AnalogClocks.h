#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class AnalogClocks : public MainComponent {
	public:
		void render();

	protected:

		uint _prevSecond = 0;

		void _drawLine(uint8_t time, uint8_t radius, uint32_t color);
		void _clear();
		void _renderFace();

};
