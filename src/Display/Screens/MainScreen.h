#pragma once

#include "Components/Time.h"
#include "Components/Date.h"
#include "Components/InfoPanel.h"

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

