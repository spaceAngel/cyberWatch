#include "config.h"

#include <LilyGoWatch.h>

#include "Watches.h"
#include "AppMenu.h"
#include "UserInterface/Components/Component.h"
#include "Core/Registry.h"
#include "Environment/AppSettings.h"
#include "UserInterface/UserInterfaceManager.h"
#include "Apps/WatchFaces/WatchFace.h"
#include "UserInterface/AppRunner.h"
#include "Apps/SettingsPanel.h"
#include "Core/Hardware/Esp32.h"

void Watches::render() {
	if (
		this->getCurrentFace()->runWithHighSpeed()
	) {
		Esp32::getInstance()->runWithCpuSpeedHigh(
			[this]() {
				this->getCurrentFace()->render();
			}
		);
	} else {
		this->getCurrentFace()->render();
	}
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

bool Watches::handleSwipeHorizontal(int8_t vector) {
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
	//AppRunner::getInstance()->setAppOnTop(new SettingsPanel());
	AppRunner::getInstance()->setAppOnTop(new AppMenu());
	return true;
}