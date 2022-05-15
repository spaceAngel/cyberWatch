#include "config.h"

#include "MainScreen.h"

#include "UserInterface/Components/Time.h"
#include "UserInterface/Components/Date.h"
#include "UserInterface/Components/InfoPanel.h"

MainScreen* MainScreen::_inst;

MainScreen *MainScreen::getInstance() {
	if (MainScreen::_inst == nullptr) {
		MainScreen::_inst = new MainScreen();
	}
	return MainScreen::_inst;
}

void MainScreen::render() {
	_time->render();
	_date->render();
	_infoPanel->render();
}

MainScreen::MainScreen() {
	_time = new Time();
	_date = new Date();
	_infoPanel = new InfoPanel();
}
