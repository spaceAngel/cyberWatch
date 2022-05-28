#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"

class Planetoid : public MainComponent {

	public:

		void render();

	protected:

		uint _prevSecond = 99;

		void _clear();
		void _renderFace();
		void _renderPoint(uint16_t angle, uint8_t radius, uint8_t size, int color);

};
