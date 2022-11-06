#pragma once

#include "UserInterface/Components/InfoPanel.h"
#include "UserInterface/App.h"
#include "UserInterface/Apps/Watches.h"
#include "UserInterface/Apps/Calendar.h"
#include "UserInterface/Apps/StopWatch.h"
#include "UserInterface/Apps/SettingsPanel.h"
#include "UserInterface/Apps/AboutPanel.h"
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
		App *getCurrentApp();

		protected:

			static MainScreen *inst;

			const int8_t APPS = 2;

			App *apps[3];
			int8_t currentApp = 0;

			App *appOnTop = nullptr;

			NotificationBar *notificationBar;

			void clear();

			void createApps() {
				this->apps[0] = new Watches();
				this->apps[1] = new Calendar();
				this->apps[2] = new StopWatch();
			}
			MainScreen();

};
