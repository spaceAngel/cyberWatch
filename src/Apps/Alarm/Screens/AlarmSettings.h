#pragma once

#include "UserInterface/App.h"

#include "Apps/Alarm/Components/Settings/AlarmSettingsTimeSpinner.h"
#include "Apps/Alarm/Components/Settings/AlarmSettingsDayButton.h"
#include "Apps/Alarm/AlarmModel.h"

class AlarmSettings : public App {

	public:

		void render();

		bool hasNotificationBar() {
			return true;
		}

		bool controlModeIsTouch() {
			return true;
		}

		bool handlePEKShort();

		bool handleTouch(uint8_t x, uint8_t y);

		AlarmSettings(uint8_t alarm);

	protected:

		const uint8_t BTN_WIDTH = 90;
		const uint8_t BTN_HEIGHT = 40;

		uint8_t alarm;

		AlarmSettingsTimeSpinner *spinnerHour;
		AlarmSettingsTimeSpinner *spinnerMinute;

		AlarmSettingsDayButton *dayButtons[7];

		void renderButtons();


};
