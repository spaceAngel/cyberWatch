#pragma once

#include "UserInterface/Components/MainPanel.h"
#include "UserInterface/Components/InfoPanel.h"

class MainScreen {

	public:

		static MainScreen *getInstance();

		void render();

		void handleSwipeHorizontal(int vector);
		void handleSwipeVertical(int vector);
		void handlePEKShort();
		bool isSleepForbidden();

		protected:

			static MainScreen *_inst;

			MainPanel *_mainPanel;
			InfoPanel *_infoPanel;

			MainScreen();

};
