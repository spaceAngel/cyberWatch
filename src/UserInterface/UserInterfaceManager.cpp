#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterfaceManager.h"

#include "UserInterface/Screens/MainScreen.h"
#include "UserInterface/Screens/SplashScreen.h"
#include "UserInterface/Screens/ExitScreen.h"
#include "UserInterface/Icons/IconStruct.h"
#include "Utils/TimeUtil.h"
#include "Core/Hardware/Display.h"
#include "Core/InactivityWatcher.h"
#include "UserInterface/Apps/MsgBoxes/Locked.h"

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
	int16_t x;
	int16_t y;
	bool handled = false;
	if (
		!TTGOClass::getWatch()->getTouch(x, y)
		|| ((x == 257) && (y == 2)) //some kind of HW error in my LILLYGO T-Watch (short circuit?)
	) {
		if (
			this->isLocked()
			&& this->lastTouched > 0
			&& this->lastTouched + LONGTOUCH_UNLOCK < millis()
			&& this->touchFromInactivity == false
		) {
			this->setIsLocked(false);
		}

		if (
			this->isLocked()
			&& this->lastTouched > 0
			&& this->lastTouched + LONGTOUCH_UNLOCK > millis()
			&& this->touchFromInactivity == false
		) {
			MainScreen::getInstance()->setAppOnTop(new Locked());
		}
		if (
			this->touchFromInactivity == false
			&& this->touchReleased == false
			&& this->swipeWasHandled == false
		)  {
			MainScreen::getInstance()->handleTouch(
				this->lastTouchX,
				this->lastTouchY,
				this->lastTouched + LONGTOUCH_INAPP < millis()
			);
		}
		this->touchReleased = true;
		this->swipeWasHandled = false;
		this->touchFromInactivity = InactivityWatcher::getInstance()->isInactive();
		this->lastTouched = 0;

	} else {
		if (this->isLocked() != true) {
			this->lastTouchX = x;
			this->lastTouchY = y;
			if (this->touchReleased == true) {
				this->touchFromInactivity = InactivityWatcher::getInstance()->isInactive();
				this->touchReleased = false;
			}
			if (this->swipeEnabled == true) {
				this->handleSwipeHorizontal(x);
				this->handleSwipeVertical(y);
			}
		}

		if (
			this->lastTouched == 0
		) {
			this->lastTouched = millis();
		}
		handled = true;
	}
	if (handled == false) {
		this->stopSwipeHandlerHorizontal();
		this->stopSwipeHandlerVertical();
	}
	return handled;
}

void UserInterfaceManager::handleSwipeHorizontal(uint x) {
	if (this->swipeVectorHorizontal == 0) {
		if ((int32_t)this->swipeLastX == 0) {
			this->swipeLastX = 0 + x;
		} else {
			if ((int32_t)this->swipeLastX < x) {
				this->swipeVectorHorizontal = VECTOR_RIGHT;
			 } else {
				this->swipeVectorHorizontal = VECTOR_LEFT;
			}
		}
	} else if (
		(
			(this->swipeVectorHorizontal == VECTOR_RIGHT) && (this->swipeLastX < (x - CROSS_SWIPE_TOLERANCE))
		) || (
			(this->swipeVectorHorizontal == VECTOR_LEFT) &&  (this->swipeLastX > (x + CROSS_SWIPE_TOLERANCE))
		)
	) {
		this->swipeCounterHorizontal++;
		this->stopSwipeHandlerVertical();
	} else {
		this->stopSwipeHandlerHorizontal();
	}
	if ((int32_t)this->swipeCounterHorizontal == 3) {
		MainScreen::getInstance()->handleSwipeHorizontal(
			(this->swipeVectorHorizontal == VECTOR_LEFT) ? -1 : 1
		);
		this->swipeWasHandled = true;
	}
}

void UserInterfaceManager::stopSwipeHandlerHorizontal() {
	this->swipeCounterHorizontal = 0;
	this->swipeLastX = 0;
	this->swipeVectorHorizontal = 0;
	if (Display::getInstance()->isDisplayOn() == true) {
		this->swipeEnabled = true;
	} else {
		this->swipeEnabled = false;
	}
}


void UserInterfaceManager::handleSwipeVertical(uint y) {
	if (this->swipeVectorVertical == 0) {
		if ((int32_t)this->swipeLastY == 0) {
			this->swipeLastY = 0 + y;
		} else {
			if (this->swipeLastY < y) {
				this->swipeVectorVertical = VECTOR_DOWN;
			 } else {
				this->swipeVectorVertical = VECTOR_UP;
			}
		}
	} else if (
		(((int32_t)this->swipeVectorVertical == VECTOR_UP) && (this->swipeLastY > y))
		|| (((int32_t)this->swipeVectorVertical == VECTOR_DOWN) && (this->swipeLastY < y))
	) {
		this->swipeCounterVertical++;
		this->stopSwipeHandlerHorizontal();
	} else {
		this->stopSwipeHandlerVertical();
	}
	if ((int32_t)this->swipeCounterVertical == 3) {
		MainScreen::getInstance()->handleSwipeVertical(
			(this->swipeVectorVertical == VECTOR_UP) ? -1 : 1
		);
		this->swipeWasHandled = true;
	}
}

void UserInterfaceManager::stopSwipeHandlerVertical() {
	this->swipeCounterVertical = 0;
	this->swipeLastY = 0;
	this->swipeVectorVertical = 0;
	if (Display::getInstance()->isDisplayOn() == true) {
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

void UserInterfaceManager::renderIcon(IconStruct icon, uint8_t x, uint8_t y) {
	TTGOClass::getWatch()->tft->setSwapBytes(true);
	TTGOClass::getWatch()->tft->pushImage(x, y, icon.width, icon.heigth, icon.data);
}

void UserInterfaceManager::setToDefaultApp() {
	MainScreen::getInstance()->setToDefaultApp();
}

bool UserInterfaceManager::isLocked() {
	return this->locked;
}

void UserInterfaceManager::setIsLocked(bool locked) {
	this->locked = locked;
}

void UserInterfaceManager::clearScreen() {
	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		TTGOClass::getWatch()->tft->width(),
		TTGOClass::getWatch()->tft->height(),
		COLOR_BACKGROUND
	);
}
