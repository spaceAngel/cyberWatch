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

	protected:

		void renderText(uint8_t line, char* text);

};
