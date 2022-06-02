#include "config.h"

#include "MainScreen.h"

#include "UserInterface/Components/MainPanel.h"
#include "UserInterface/Components/InfoPanel.h"

MainScreen* MainScreen::inst;

MainScreen *MainScreen::getInstance() {
	if (MainScreen::inst == nullptr) {
		MainScreen::inst = new MainScreen();
	}
	return MainScreen::inst;
}

void MainScreen::render() {
	this->mainPanel->render();
	this->infoPanel->render();
}

MainScreen::MainScreen() {
	this->mainPanel = new MainPanel();
	this->infoPanel = new InfoPanel();
}

void MainScreen::handleSwipeHorizontal(int vector) {
	this->mainPanel->switchApp(vector);
}

void MainScreen::handleSwipeVertical(int vector) {
	this->mainPanel->handleSwipeVertical(vector);
}

void MainScreen::handlePEKShort() {
	this->mainPanel->handlePEKShort();
}

bool MainScreen::isSleepForbidden() {
	return this->mainPanel->isSleepForbidden();
}
