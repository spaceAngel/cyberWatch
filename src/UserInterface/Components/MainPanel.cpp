#include "config.h"

#include <LilyGoWatch.h>

#include "MainPanel.h"
#include "Core/Registry.h"

void MainPanel::render() {
	this->getCurrentComponent()->render();
};

void MainPanel::switchApp(int vector) {
	this->getCurrentComponent()->setIsActive(false);
	this->currentApp += vector;
	if (this->currentApp > APPS) {
		this->currentApp = 0;
	}

	if (this->currentApp < 0) {
		this->currentApp = APPS;
	}

	this->getCurrentComponent()->setShouldReRender(true);
	this->getCurrentComponent()->setIsActive(true);
	Registry::getInstance()->setValue(Registry::NAME_APP, this->currentApp);
	this->clear();
	this->render();
}

void MainPanel::handleSwipeVertical(int8_t vector) {
	if (this->getCurrentComponent()->handleSwipeVertical(vector) == true) {
		this->clear();
	}
}

void MainPanel::clear() {
	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		TTGOClass::getWatch()->tft->width(),
		150,
		COLOR_BACKGROUND
	);

}

void MainPanel::handlePEKShort() {
	if (this->getCurrentComponent()->handlePEKShort() == true) {
		this->clear();
	}
}

bool MainPanel::isSleepForbidden() {
	bool rslt = false;
	for (int8_t i = 0; i <= APPS; i++) {
		if (apps[i]->isSystemSleepForbidden() == true) {
			rslt = true;
		}
	}
	return rslt;
}
void MainPanel::handleTouch(uint8_t x, uint8_t y) {
	if (this->getCurrentComponent()->controlModeIsTouch() == true) {
		if (this->getCurrentComponent()->handleTouch(x, y) == true) {
			this->clear();
		}
	}
}

MainComponent *MainPanel::getCurrentComponent() {
	return this->apps[this->currentApp];
}

MainPanel::MainPanel() {
	this->createApps();
	uint currentApp = Registry::getInstance()->getValue(Registry::NAME_APP);
	if (
		(currentApp >= 0)
		&& (currentApp <= APPS)
	) {
		this->currentApp = currentApp;
	}
}

