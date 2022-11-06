#include "config.h"

#include "MainScreen.h"

#include "UserInterface/Components/NotificationBar/NotificationBar.h"

MainScreen* MainScreen::inst;

MainScreen *MainScreen::getInstance() {
	if (MainScreen::inst == nullptr) {
		MainScreen::inst = new MainScreen();
	}
	return MainScreen::inst;
}

void MainScreen::render() {
	this->getCurrentApp()->render();
	if (this->getCurrentApp()->hasNotificationBar()) {
		this->notificationBar->render();
	}
}

MainScreen::MainScreen() {
	this->createApps();
	this->notificationBar = new NotificationBar();
}

void MainScreen::handleSwipeHorizontal(int vector) {
	this->getCurrentApp()->setIsActive(false);
	this->currentApp += vector;
	if (this->currentApp > APPS) {
		this->currentApp = 0;
	}

	if (this->currentApp < 0) {
		this->currentApp = APPS;
	}

	this->getCurrentApp()->setShouldReRender(true);
	this->notificationBar->setShouldReRender(true);
	this->getCurrentApp()->setIsActive(true);
	this->clear();
	this->render();
}

void MainScreen::handleSwipeVertical(int vector) {
	if (this->getCurrentApp()->handleSwipeVertical(vector) == true) {
		this->clear();
		this->notificationBar->setShouldReRender(true);
	}
}

void MainScreen::handlePEKShort() {
	if (this->getCurrentApp()->handlePEKShort() == true) {
		this->clear();
	}
}

bool MainScreen::isSleepForbidden() {
	bool rslt = false;
	for (int8_t i = 0; i <= APPS; i++) {
		if (apps[i]->isSystemSleepForbidden() == true) {
			rslt = true;
		}
	}
	return rslt;
}

void MainScreen::handleTouch(uint8_t x, uint8_t y, bool isLongTouch ){
	if (
		this->getCurrentApp()->canHandleLongTouch() == true
		&& isLongTouch
	) {
		if (this->getCurrentApp()->handleLongTouch(x, y) == true) {
			this->clear();
		}
	} else  if (this->getCurrentApp()->controlModeIsTouch() == true) {
		if (this->getCurrentApp()->handleTouch(x, y) == true) {
			this->clear();
		}
	}
}

void  MainScreen::setToDefaultApp() {
	if (
		this->currentApp != 0
		|| this->appOnTop != nullptr
	) {
		this->clear();
		this->currentApp = 0;
		this->apps[0]->setShouldReRender(true);
		this->notificationBar->setShouldReRender(true);

		delete this->appOnTop;
		this->appOnTop = NULL;
	}
}

void MainScreen::clear() {
	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		TTGOClass::getWatch()->tft->width(),
		TTGOClass::getWatch()->tft->height(),
		COLOR_BACKGROUND
	);
}

App *MainScreen::getCurrentApp() {
	return this->appOnTop == nullptr ? this->apps[this->currentApp] : this->appOnTop;
}

void MainScreen::setAppOnTop(App* appOnTop) {
	this->appOnTop = appOnTop;
}
