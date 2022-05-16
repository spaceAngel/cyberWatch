#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterfaceManager.h"

#include "UserInterface/Screens/MainScreen.h"
#include "UserInterface/Screens/SplashScreen.h"
#include "UserInterface/Screens/ExitScreen.h"
#include "Utils/TimeUtil.h"
#include "System/Display.h"

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
		if (_swipeEnabled) {
			_handleSwipe(x);
		}
		return true;
	}

	_stopSwipeHandler();
	return false;
}

void UserInterfaceManager::_handleSwipe(uint x) {
	if (_swipeVector == 0) {
		if (_swipeLastX == 0) {
			_swipeLastX = 0 + x;
		} else {
			if (_swipeLastX < x) {
				_swipeVector = VECTOR_RIGHT;
			 } else {
				_swipeVector = VECTOR_LEFT;
			}
		}
	} else {

		if (
			(_swipeVector == VECTOR_RIGHT && _swipeLastX < x)
			|| (_swipeVector == VECTOR_LEFT &&  _swipeLastX > x)
		) {
			_swipeCounter++;
		} else {
			_stopSwipeHandler();
		}
	}
	if (_swipeCounter == 2) {
		MainScreen::getInstance()->handleSwipe(
			_swipeVector == VECTOR_LEFT ? -1 : 1
		);
		//TO-DO: handle swipe
	}
}

void UserInterfaceManager::_stopSwipeHandler() {
	_swipeCounter = 0;
	_swipeLastX = 0;
	_swipeVector = 0;
	if (Display::getInstance()->isDisplayOn()) {
		_swipeEnabled = true;
	} else {
		_swipeEnabled = false;
	}
}
