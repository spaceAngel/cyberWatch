#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"

class SettingsPanelButton : public MainComponent {

	public:

		SettingsPanelButton(
			char *btnText,
			uint8_t col,
			uint8_t row,
			std::function<bool(void)> isActiveFunc,
			std::function<bool()> handleTouchFunc
		);

		uint8_t getX();
		uint8_t getY();
		uint8_t getWidth();
		uint8_t getHeight();

		void render();
		bool handleTouch();

	protected:

		uint8_t col;
		uint8_t row;
		std::function<bool()> isActiveFunc;
		std::function<bool()> handleTouchFunc;

		char *btnText;
};
