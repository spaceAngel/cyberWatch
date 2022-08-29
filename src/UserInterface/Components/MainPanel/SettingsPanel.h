#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"

class SettingsPanel : public MainComponent {

	public:

		void render();
		bool handlePEKShort();

		SettingsPanel();
		bool controlModeIsTouch();
		bool handleTouch(uint8_t x, uint8_t y);

	protected:

		uint8_t lastMask;

		void renderButton(char *btnText, uint8_t col, uint8_t row, boolean isOn);
		void renderDisplayButton();

		bool handleDisplayButtonClick(uint8_t x, uint8_t y);
};
