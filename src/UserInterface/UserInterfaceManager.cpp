#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterfaceManager.h"

#include "UserInterface/Screens/MainScreen.h"
#include "UserInterface/Screens/SplashScreen.h"
#include "UserInterface/Screens/ExitScreen.h"
#include "Utils/TimeUtil.h"
#include "System/Display.h"

UserInterfaceManager *UserInterfaceManager::inst;


UserInterfaceManager *UserInterfaceManager::getInstance() {
	if (UserInterfaceManager::inst == nullptr) {
		UserInterfaceManager::inst = new UserInterfaceManager();
	}
	return UserInterfaceManager::inst;
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
		if (this->swipeEnabled) {
			this->handleSwipeHorizontal(x);
			this->handleSwipeVertical(y);
		}
		return true;
	}

	this->stopSwipeHandlerHorizontal();
	this->stopSwipeHandlerVertical();
	return false;
}

void UserInterfaceManager::handleSwipeHorizontal(uint x) {
	if (this->swipeVectorHorizontal == 0) {
		if (this->swipeLastX == 0) {
			this->swipeLastX = 0 + x;
		} else {
			if (this->swipeLastX < x) {
				this->swipeVectorHorizontal = VECTOR_RIGHT;
			 } else {
				this->swipeVectorHorizontal = VECTOR_LEFT;
			}
		}
	} else {

		if (
			(
				this->swipeVectorHorizontal == VECTOR_RIGHT && this->swipeLastX < x - CROSS_SWIPE_TOLERANCE
			) || (
				this->swipeVectorHorizontal == VECTOR_LEFT &&  this->swipeLastX > x + CROSS_SWIPE_TOLERANCE
			)
		) {
			this->swipeCounterHorizontal++;
			this->stopSwipeHandlerVertical();
		} else {
			this->stopSwipeHandlerHorizontal();
		}
	}
	if (this->swipeCounterHorizontal == 3) {
		MainScreen::getInstance()->handleSwipeHorizontal(
			this->swipeVectorHorizontal == VECTOR_LEFT ? -1 : 1
		);
	}
}

void UserInterfaceManager::stopSwipeHandlerHorizontal() {
	this->swipeCounterHorizontal = 0;
	this->swipeLastX = 0;
	this->swipeVectorHorizontal = 0;
	if (Display::getInstance()->isDisplayOn()) {
		this->swipeEnabled = true;
	} else {
		this->swipeEnabled = false;
	}
}


void UserInterfaceManager::handleSwipeVertical(uint y) {
	if (this->swipeVectorVertical == 0) {
		if (this->swipeLastY == 0) {
			this->swipeLastY = 0 + y;
		} else {
			if (this->swipeLastY < y) {
				this->swipeVectorVertical = VECTOR_DOWN;
			 } else {
				this->swipeVectorVertical = VECTOR_UP;
			}
		}
	} else {

		if (
			(this->swipeVectorVertical == VECTOR_UP && this->swipeLastY > y)
			|| (this->swipeVectorVertical == VECTOR_DOWN &&  this->swipeLastY < y)
		) {
			this->swipeCounterVertical++;
			this->stopSwipeHandlerHorizontal();
		} else {
			this->stopSwipeHandlerVertical();
		}
	}
	if (this->swipeCounterVertical == 3) {
		MainScreen::getInstance()->handleSwipeVertical(
			this->swipeVectorVertical == VECTOR_UP ? -1 : 1
		);
	}
}

void UserInterfaceManager::stopSwipeHandlerVertical() {
	this->swipeCounterVertical = 0;
	this->swipeLastY = 0;
	this->swipeVectorVertical = 0;
	if (Display::getInstance()->isDisplayOn()) {
		this->swipeEnabled = true;
	} else {
		this->swipeEnabled = false;
	}
}

void UserInterfaceManager::handlePEKShort() {
	MainScreen::getInstance()->handlePEKShort();
}

bool UserInterfaceManager::isSleepForbidden() {
	return MainScreen::getInstance()->isSleepForbidden();
}