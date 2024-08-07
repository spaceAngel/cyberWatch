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

		void setAppOnTop(App* app);
		void removeAppOnTop();
		void setToDefaultApp();
		bool isSleepForbidden();

		App *getCurrentApp();

	protected:

		static AppRunner *inst;

		App *appOnTop = nullptr;
		App *defaultApp = nullptr;

		AppRunner();

		void createApps() {
			this->defaultApp = new Watches();
		}


};
