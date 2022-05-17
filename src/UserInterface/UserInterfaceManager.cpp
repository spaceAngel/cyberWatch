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
			_handleSwipeHorizontal(x);
			_handleSwipeVertical(y);
		}
		return true;
	}

	_stopSwipeHandlerHorizontal();
	_stopSwipeHandlerVertical();
	return false;
}

void UserInterfaceManager::_handleSwipeHorizontal(uint x) {
	if (_swipeVectorHorizontal == 0) {
		if (_swipeLastX == 0) {
			_swipeLastX = 0 + x;
		} else {
			if (_swipeLastX < x) {
				_swipeVectorHorizontal = VECTOR_RIGHT;
			 } else {
				_swipeVectorHorizontal = VECTOR_LEFT;
			}
		}
	} else {

		if (
			(_swipeVectorHorizontal == VECTOR_RIGHT && _swipeLastX < x)
			|| (_swipeVectorHorizontal == VECTOR_LEFT &&  _swipeLastX > x)
		) {
			_swipeCounterHorizontal++;
		} else {
			_stopSwipeHandlerHorizontal();
		}
	}
	if (_swipeCounterHorizontal == 4) {
		MainScreen::getInstance()->handleSwipeHorizontal(
			_swipeVectorHorizontal == VECTOR_LEFT ? -1 : 1
		);
	}
}

void UserInterfaceManager::_stopSwipeHandlerHorizontal() {
	_swipeCounterHorizontal = 0;
	_swipeLastX = 0;
	_swipeVectorHorizontal = 0;
	if (Display::getInstance()->isDisplayOn()) {
		_swipeEnabled = true;
	} else {
		_swipeEnabled = false;
	}
}


void UserInterfaceManager::_handleSwipeVertical(uint y) {
	if (_swipeVectorVertical == 0) {
		if (_swipeLastY == 0) {
			_swipeLastY = 0 + y;
		} else {
			if (_swipeLastY < y) {
				_swipeVectorVertical = VECTOR_DOWN;
			 } else {
				_swipeVectorVertical = VECTOR_UP;
			}
		}
	} else {

		if (
			(_swipeVectorVertical == VECTOR_UP && _swipeLastY > y)
			|| (_swipeVectorVertical == VECTOR_DOWN &&  _swipeLastY < y)
		) {
			_swipeCounterVertical++;
		} else {
			_stopSwipeHandlerVertical();
		}
	}
	if (_swipeCounterVertical == 3) {
		MainScreen::getInstance()->handleSwipeVertical(
			_swipeVectorVertical == VECTOR_UP ? -1 : 1
		);
	}
}

void UserInterfaceManager::_stopSwipeHandlerVertical() {
	_swipeCounterVertical = 0;
	_swipeLastY = 0;
	_swipeVectorVertical = 0;
	if (Display::getInstance()->isDisplayOn()) {
		_swipeEnabled = true;
	} else {
		_swipeEnabled = false;
	}
}
