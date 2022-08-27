#pragma once

#include <Arduino.h>

#define APPSETTINGS_ALWAYS_ON 1

class AppSettings {

	public:

		static AppSettings *getInstance();

		uint8_t getSettingsByteMask();

		void setAlwaysOn(bool alwaysOn);
		bool getAlwaysOn();

		protected:

			static AppSettings *inst;

			uint8_t bits;

			AppSettings();

};
