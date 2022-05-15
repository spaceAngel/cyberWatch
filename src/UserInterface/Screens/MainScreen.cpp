#include "config.h"

#include "MainScreen.h"

#include "UserInterface/Components/DateTime.h"
#include "UserInterface/Components/InfoPanel.h"

MainScreen* MainScreen::_inst;

MainScreen *MainScreen::getInstance() {
	if (MainScreen::_inst == nullptr) {
		MainScreen::_inst = new MainScreen();
	}
	return MainScreen::_inst;
}

void MainScreen::render() {
	_dateTime->render();
	_infoPanel->render();
}

MainScreen::MainScreen() {
	_dateTime = new DateTime();
	_infoPanel = new InfoPanel();
}
