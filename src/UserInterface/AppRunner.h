#pragma once

#include <Arduino.h>

#include "UserInterface/App.h"

#include "Apps/Watches.h"
#include "Apps/Calendar.h"
#include "Apps/StopWatch.h"
#include "Apps/Alarm.h"

class AppRunner {

	public:

		static AppRunner *getInstance();

		void switchToPrevApp();
		void switchToNextApp();
		void setAppOnTop(App* app);
		void removeAppOnTop();
		void setToDefaultApp();
		bool isSleepForbidden();

		App *getCurrentApp();

	protected:

		static AppRunner *inst;

		const int8_t APPS = 3;

		App *apps[4];
		int8_t currentApp = 0;

		App *appOnTop = nullptr;

		AppRunner();


		void createApps() {
			this->apps[0] = new Watches();
			this->apps[1] = new Calendar();
			this->apps[2] = new StopWatch();
			this->apps[3] = new Alarm();
		}


};
