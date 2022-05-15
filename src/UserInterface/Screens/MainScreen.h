#pragma once

#include "UserInterface/Components/DateTime.h"
#include "UserInterface/Components/InfoPanel.h"

class MainScreen {

	public:

		static MainScreen *getInstance();

		void render();

		protected:

			static MainScreen *_inst;

			DateTime *_dateTime;
			InfoPanel *_infoPanel;

			MainScreen();

};
