#include "config.h"

#include <LilyGoWatch.h>

#include "Watches.h"
#include "UserInterface/Components/MainComponent.h"
#include "Core/Registry.h"
#include "Environment/AppSettings.h"
#include "UserInterface/UserInterfaceManager.h"
#include "UserInterface/WatchFaces/WatchFace.h"
#include "UserInterface/Screens/MainScreen.h"
#include "UserInterface/Apps/SettingsPanel.h"

void Watches::render() {
	this->getCurrentFace()->render();
	if (this->getCurrentFace()->hasInfoPanel()) {
		this->infoPanel->render();
	}
}

void Watches::setShouldReRender(bool shouldReRender) {
	for (int32_t i = 0; i <= FACES; i++) {
		this->clockFaces[i]->setShouldReRender(shouldReRender);
	}
	this->infoPanel->setShouldReRender(shouldReRender);
}

bool Watches::handleSwipeVertical(int8_t vector) {
	this->currentFace += vector;
	if (this->currentFace > FACES) {
		this->currentFace = 0;
	}
	if (this->currentFace < 0) {
		this->currentFace = FACES;
	}

	Registry::getInstance()->setValue(Registry::NAME_WATCH_FACE, this->currentFace);
	UserInterfaceManager::getInstance()->clearScreen();
	this->getCurrentFace()->setShouldReRender(true);
	this->infoPanel->setShouldReRender(true);
	return true;
}

WatchFace *Watches::getCurrentFace() {
	return this->clockFaces[this->currentFace];
}

bool Watches::handlePEKShort() {
	UserInterfaceManager::getInstance()->setIsLocked(
		!UserInterfaceManager::getInstance()->isLocked()
	);
	return false;
}

bool Watches::hasNotificationBar() {
	return this->getCurrentFace()->hasToolbar();
}

Watches::Watches() {
	this->infoPanel = new InfoPanel();
	this->createFaces();
	uint currentFace = Registry::getInstance()->getValue(Registry::NAME_WATCH_FACE);
	if (
		(currentFace >= 0)
		&& (currentFace <= FACES)
	) {
		this->currentFace = currentFace;
	}
}


bool Watches::handleLongTouch(uint8_t x, uint8_t y) {
	MainScreen::getInstance()->setAppOnTop(new SettingsPanel());
	return true;
}