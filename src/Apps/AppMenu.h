#pragma once

#include "UserInterface/App.h"

#include <Arduino.h>

#include "Alarm/Components/AlarmDisplay.h"
#include "AppMenu/AppIcon.h"

class AppMenu : public App {

	public:

		void render();

		AppMenu();

		virtual bool hasNotificationBar() {
			return false;
		}

		virtual bool controlModeIsTouch() {
			return true;
		}

		virtual bool handleTouch(uint8_t x, uint8_t y);

	protected:

		void renderIcon(AppIcon icon, uint8_t x, uint8_t y);

};
