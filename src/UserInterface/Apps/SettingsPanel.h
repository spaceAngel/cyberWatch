#pragma once

#include <Arduino.h>

#include "UserInterface/App.h"
#include "UserInterface/Components/MainPanel/SubComponents/SettingsPanelButton.h"
#include "Environment/AppSettings.h"

#define ADJUSTBAR_HEIGHT 24
#define ADJUSTBAR_POSY 158

class SettingsPanel : public App {

	public:

		void render();

		SettingsPanel() {
			this->lastMask = AppSettings::getInstance()->getSettingsByteMask();
			this->buttons[0] = new SettingsPanelButton(
				"Display", 1, 1,
				[]() {return AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON);},
				[]() {AppSettings::getInstance()->toggle(APPSETTINGS_ALWAYS_ON);}
			);
			this->buttons[1] = new SettingsPanelButton(
				"Tilt", 2, 1,
				[]() {return AppSettings::getInstance()->get(APPSETTINGS_TILT_ON);},
				[]() {AppSettings::getInstance()->toggle(APPSETTINGS_TILT_ON);}
			);
			this->buttons[2] = new SettingsPanelButton(
				"Vibrate", 1, 2,
				[]() {return AppSettings::getInstance()->get(APPSETTINGS_VIBRATE);},
				[]() {AppSettings::getInstance()->toggle(APPSETTINGS_VIBRATE);}
			);
			this->buttons[3] = new SettingsPanelButton("Sound", 2, 2, []() {return false;}, []() {});

		}
		bool controlModeIsTouch();
		bool handleTouch(uint8_t x, uint8_t y);
		void setShouldReRender(bool shouldReRender);
		bool canHandleLongTouch() {
			return true;
		}

		bool handleLongTouch(uint8_t x, uint8_t y);

		bool handlePEKShort();

	protected:

		uint8_t lastMask;

		const int BUTTONS = 3;
		SettingsPanelButton *buttons[4];

		void renderAdjustBar();

		void handleTouchAdjustbar(uint8_t x);
		void handleTouchButtons(uint8_t x, uint8_t y);

};
