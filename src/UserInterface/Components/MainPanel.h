#pragma once

#include "UserInterface/Components/MainPanel/DateTime.h"
#include "UserInterface/Components/MainPanel/Calendar.h"
#include "UserInterface/Components/MainPanel/StopWatch.h"
#include "UserInterface/Components/MainPanel/SettingsPanel.h"
#include "UserInterface/Components/MainComponent.h"
#include "System/AppsStatusMonitor.h"

class MainPanel {

	public:

		MainPanel();

		void render();
		void switchApp(int vector);
		void handleSwipeVertical(int8_t vector);
		void handleTouch(uint8_t x, uint8_t y);
		void handlePEKShort();
		bool isSleepForbidden();
		MainComponent *getCurrentComponent();

	protected:

		const int8_t APPS = 3;

		MainComponent *apps[4];
		int8_t currentApp = 0;

		void clear();

		void createApps() {
			this->apps[0] = new DateTime();
			this->apps[1] = new Calendar();
			this->apps[2] = new StopWatch();
			this->apps[3] = new SettingsPanel();
		}

};
