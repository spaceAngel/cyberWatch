#include "config.h"

#include "MainScreen.h"

#include "UserInterface/Components/NotificationBar/NotificationBar.h"
#include "UserInterface/AppRunner.h"

MainScreen* MainScreen::inst;

MainScreen *MainScreen::getInstance() {
	if (MainScreen::inst == nullptr) {
		MainScreen::inst = new MainScreen();
	}
	return MainScreen::inst;
}

void MainScreen::render() {
	AppRunner::getInstance()->getCurrentApp()->render();
	if (AppRunner::getInstance()->getCurrentApp()->hasNotificationBar()) {
		this->notificationBar->render();
	}
}

MainScreen::MainScreen() {
	this->notificationBar = new NotificationBar();
}

void MainScreen::handleSwipeHorizontal(int vector) {
	AppRunner::getInstance()->getCurrentApp()->setIsActive(false);
	if (vector > 0) {
		AppRunner::getInstance()->switchToPrevApp();
	} else {
		AppRunner::getInstance()->switchToNextApp();
	}

	AppRunner::getInstance()->getCurrentApp()->setShouldReRender(true);
	this->notificationBar->setShouldReRender(true);
	AppRunner::getInstance()->getCurrentApp()->setIsActive(true);
	this->clear();
	this->render();
}

void MainScreen::handleSwipeVertical(int vector) {
	if (AppRunner::getInstance()->getCurrentApp()->handleSwipeVertical(vector) == true) {
		this->clear();
		this->notificationBar->setShouldReRender(true);
	}
}

void MainScreen::handlePEKShort() {
	if (AppRunner::getInstance()->getCurrentApp()->handlePEKShort() == true) {
		this->clear();
	}
}

void MainScreen::handleTouch(uint8_t x, uint8_t y, bool isLongTouch ){
	if (
		AppRunner::getInstance()->getCurrentApp()->canHandleLongTouch() == true
		&& isLongTouch
	) {
		if (AppRunner::getInstance()->getCurrentApp()->handleLongTouch(x, y) == true) {
			this->clear();
		}
	} else  if (AppRunner::getInstance()->getCurrentApp()->controlModeIsTouch() == true) {
		if (AppRunner::getInstance()->getCurrentApp()->handleTouch(x, y) == true) {
			this->clear();
		}
	}
}

NotificationBar *MainScreen::getNotificationBar() {
	return this->notificationBar;
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

void MainScreen::destroy() {
	delete MainScreen::inst;
	MainScreen::inst = NULL;
}
