#pragma once

#include "UserInterface/App.h"

#include <Arduino.h>

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
		bool handlePEKShort();

		uint16_t getAllowedTimeWithoutActivity() {
			return 20;
		}

		bool onSwipeDown();

	protected:

		void renderIcon(const uint16_t *icon, uint8_t x, uint8_t y);

};
