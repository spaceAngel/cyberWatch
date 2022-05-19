#include "config.h"

#include "MainScreen.h"

#include "UserInterface/Components/MainPanel.h"
#include "UserInterface/Components/InfoPanel.h"

MainScreen* MainScreen::_inst;

MainScreen *MainScreen::getInstance() {
	if (MainScreen::_inst == nullptr) {
		MainScreen::_inst = new MainScreen();
	}
	return MainScreen::_inst;
}

void MainScreen::render() {
	_mainPanel->render();
	_infoPanel->render();
}

MainScreen::MainScreen() {
	_mainPanel = new MainPanel();
	_infoPanel = new InfoPanel();
}

void MainScreen::handleSwipeHorizontal(int vector) {
	_mainPanel->switchScreen(vector);
}

void MainScreen::handleSwipeVertical(int vector) {
	_mainPanel->handleSwipeVertical(vector);
}

void MainScreen::handlePEKShort() {
	_mainPanel->handlePEKShort();
}

bool MainScreen::isSleepForbidden() {
	return _mainPanel->isSleepForbidden();
}
