#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterfaceManager.h"

#include "UserInterface/Screens/MainScreen.h"
#include "UserInterface/Screens/SplashScreen.h"
#include "UserInterface/Screens/ExitScreen.h"
#include "Utils/TimeUtil.h"

UserInterfaceManager *UserInterfaceManager::_inst;


UserInterfaceManager *UserInterfaceManager::getInstance() {
	if (UserInterfaceManager::_inst == nullptr) {
		UserInterfaceManager::_inst = new UserInterfaceManager();
	}
	return UserInterfaceManager::_inst;
}

void UserInterfaceManager::showSplashScreen() {
	SplashScreen *screen = new SplashScreen();
	screen->show();
}

void UserInterfaceManager::showExitScreen() {
	ExitScreen *screen = new ExitScreen();
	screen->show();
}

void UserInterfaceManager::render() {
	MainScreen::getInstance()->render();
}

bool UserInterfaceManager::handleTouch() {
	int16_t x, y;
	if (
		TTGOClass::getWatch()->getTouch(x, y)
		&& (x != 257 && y != 2) //some kind of HW error in my LILLYGO T-Watch (short circuit?)
	) {
		return true;
	}
	return false;
}