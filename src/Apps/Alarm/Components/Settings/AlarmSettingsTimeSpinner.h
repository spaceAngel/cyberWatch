#pragma once

#include "UserInterface/Components/Component.h"

class AlarmSettingsTimeSpinner : public Component {

	public:
		static const uint8_t POS_Y = 52;

		void render();

		bool handleTouch(uint8_t x, uint8_t y);

		AlarmSettingsTimeSpinner(
			uint8_t posX,
			uint8_t maxValue,
			std::function<uint8_t()> getter,
			std::function<void(uint8_t)> setter
		) {
			this->posX = posX;
			this->getter = getter;
			this->setter = setter;
			this->maxValue = maxValue;
		}

	protected:

		const uint8_t TRIANGLE_HEIGHT = 26;
		const uint8_t WIDTH = 60;
		uint8_t posX;
		uint8_t value;
		uint8_t maxValue;

		std::function<uint8_t()> getter;
		std::function<void(uint8_t)> setter;

		void renderTriangleButtons();
};
