#include "UserInterface/AppRunner.h"


#include "UserInterface/Screens/MainScreen.h"

AppRunner* AppRunner::inst;

AppRunner *AppRunner::getInstance() {
	if (AppRunner::inst == nullptr) {
		AppRunner::inst = new AppRunner();
	}
	return AppRunner::inst;
}

AppRunner::AppRunner() {
	this->createApps();
}

void  AppRunner::setToDefaultApp() {
	if (
		this->currentApp != 0
		|| this->appOnTop != nullptr
	) {
		MainScreen::getInstance()->clear();
		this->currentApp = 0;
		this->apps[0]->setShouldReRender(true);
		MainScreen::getInstance()->getNotificationBar()->setShouldReRender(true);
		delete this->appOnTop;
		this->appOnTop = NULL;
	}
}

void AppRunner::removeAppOnTop() {
	delete this->appOnTop;
	this->appOnTop = NULL;
	MainScreen::getInstance()->clear();
	this->getCurrentApp()->setShouldReRender(true);
	if (this->getCurrentApp()->hasNotificationBar()) {
		MainScreen::getInstance()->getNotificationBar()->setShouldReRender(true);
	}
	MainScreen::getInstance()->render();
}

App *AppRunner::getCurrentApp() {
	return this->appOnTop == nullptr ? this->apps[this->currentApp] : this->appOnTop;
}

void AppRunner::setAppOnTop(App* appOnTop) {
	this->appOnTop = appOnTop;
	if (this->appOnTop->hasNotificationBar()) {
		MainScreen::getInstance()->getNotificationBar()->setShouldReRender(true);
	}
	MainScreen::getInstance()->clear();
	this->appOnTop->setShouldReRender(true);
}

void AppRunner::switchToNextApp() {

}

void AppRunner::switchToPrevApp() {

}


bool AppRunner::isSleepForbidden() {
	bool rslt = false;
	return rslt;
}
