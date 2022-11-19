#pragma once

#include "UserInterface/Components/InfoPanel.h"
#include "UserInterface/App.h"
#include "Apps/Watches.h"
#include "Apps/Calendar.h"
#include "Apps/StopWatch.h"
#include "Apps/SettingsPanel.h"
#include "Apps/AboutPanel.h"
#include "Apps/Alarm.h"
#include "Core/AppsStatusMonitor.h"
#include "UserInterface/Components/NotificationBar/NotificationBar.h"

class MainScreen {

	public:

		static MainScreen *getInstance();

		void render();

		void handleSwipeHorizontal(int vector);
		void handleSwipeVertical(int vector);
		void handlePEKShort();
		bool isSleepForbidden();
		void handleTouch(uint8_t x, uint8_t y, bool isLongTouch);
		void setToDefaultApp();
		void switchApp(int vector);
		void setAppOnTop(App* app);
		void removeAppOnTop();
		void destroy();

		App *getCurrentApp();

		protected:

			static MainScreen *inst;

			const int8_t APPS = 3;

			App *apps[4];
			int8_t currentApp = 0;

			App *appOnTop = nullptr;

			NotificationBar *notificationBar;

			void clear();

			void createApps() {
				this->apps[0] = new Watches();
				this->apps[1] = new Calendar();
				this->apps[2] = new StopWatch();
				this->apps[3] = new Alarm();
			}
			MainScreen();

};
