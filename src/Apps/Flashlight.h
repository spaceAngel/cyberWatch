#pragma once

#include <Arduino.h>

#include "UserInterface/App.h"

class Flashlight : public App {

	public:

		Flashlight();

		void render();
		bool handlePEKShort();

		bool isSystemSleepForbidden() {
			return false;
		}


	protected:

		uint8_t displayAdjust;

};
