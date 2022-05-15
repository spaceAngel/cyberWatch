#pragma once

#include "UserInterface/Components/Time.h"
#include "UserInterface/Components/Date.h"
#include "UserInterface/Components/InfoPanel.h"

class MainScreen {

	public:

		static MainScreen *getInstance();

		void render();

		protected:

			static MainScreen *_inst;

			Time *_time;
			Date *_date;
			InfoPanel *_infoPanel;

			MainScreen();

};

