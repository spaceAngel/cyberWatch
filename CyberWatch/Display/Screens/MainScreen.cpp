#pragma once

#include "Components/Time.cpp"
#include "Components/Date.cpp"
#include "Components/InfoPanel.cpp"

#include <LilyGoWatch.h>

class MainScreen {

	public:

		static MainScreen *getInstance()
		{
				if (MainScreen::_inst == nullptr) {
						MainScreen::_inst = new MainScreen();
				}
				return MainScreen::_inst;
		}

		void render() {
			//_renderLogo();
			_time->render();
			_date->render();
			_infoPanel->render();
		}

		void rerender() {			
		}

		protected:

			static MainScreen *_inst;

			Time *_time;
			Date *_date;
			InfoPanel *_infoPanel;

			MainScreen() {
				_time = new Time();
				_date = new Date();
				_infoPanel = new InfoPanel();
			}

};

MainScreen* MainScreen::_inst;
