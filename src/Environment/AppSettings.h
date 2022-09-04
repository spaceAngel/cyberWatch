#pragma once

#include <Arduino.h>

#define APPSETTINGS_ALWAYS_ON 1
#define APPSETTINGS_TILT_ON 2
#define APPSETTINGS_VIBRATE 4

class AppSettings {

	public:

		static AppSettings *getInstance();

		uint8_t getSettingsByteMask();

		void set(uint8_t bit, bool value);
		void toggle(uint8_t bit);
		bool get(uint8_t bit);


		protected:

			static AppSettings *inst;

			uint8_t bits = 0;

			AppSettings();

};
