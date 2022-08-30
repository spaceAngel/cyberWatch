#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/SubComponents/SettingsPanelButton.h"
#include "Environment/AppSettings.h"
#include "System/MotorController.h"

class SettingsPanel : public MainComponent {

	public:

		void render();
		bool handlePEKShort();

		SettingsPanel() {
			this->lastMask = AppSettings::getInstance()->getSettingsByteMask();
			this->buttons[0] = new SettingsPanelButton(
				"Display", 1, 1,
				[]() {return AppSettings::getInstance()->getAlwaysOn();},
				[]() {AppSettings::getInstance()->switchAlwaysOn();return true;}
			);
			this->buttons[1] = new SettingsPanelButton("Tilt", 2, 1, []() {return true;}, [this]() {return false;});
			this->buttons[2] = new SettingsPanelButton("Vibrate", 1, 2, []() {return true;}, [this]() {return false;});
			this->buttons[3] = new SettingsPanelButton("Sound", 2, 2, []() {return false;}, [this]() {return false;});

		}
		bool controlModeIsTouch();
		bool handleTouch(uint8_t x, uint8_t y);

	protected:

		uint8_t lastMask;

		const int BUTTONS = 3;
		SettingsPanelButton *buttons[4];

};
