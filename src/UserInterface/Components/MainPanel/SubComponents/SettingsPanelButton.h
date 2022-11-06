#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class SettingsPanelButton : public Component {

	public:

		SettingsPanelButton(
			char *btnText,
			uint8_t col,
			uint8_t row,
			std::function<bool(void)> isActiveFunc,
			std::function<void()> handleTouchFunc
		);

		uint8_t getX();
		uint8_t getY();
		uint8_t getWidth();
		uint8_t getHeight();

		void render();
		void handleTouch();

	protected:

		uint8_t col;
		uint8_t row;
		std::function<bool()> isActiveFunc;
		std::function<void()> handleTouchFunc;
		bool prevValue = false;

		char *btnText;
};
