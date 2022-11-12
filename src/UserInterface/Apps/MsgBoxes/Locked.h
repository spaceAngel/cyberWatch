#pragma once

#include "UserInterface/App.h"
#include <Arduino.h>

class Locked : public App {

	public:
		void render();

		bool handlePEKShort();

		bool hasNotificationBar() {
			return false;
		}

		bool canBeTouchedLocked() {
			return true;
		}

		bool controlModeIsTouch() {
			return true;
		}

		bool canHandleLongTouch() {
			return true;
		}

		bool handleLongTouch(uint8_t x, uint8_t y);
		bool handleTouch(uint8_t x, uint8_t y);

	protected:

		void renderText(uint8_t line, const char* text);

};
