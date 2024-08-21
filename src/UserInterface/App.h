#pragma once

#define APP_POSITION_TOP 28

#include <Arduino.h>
#include "config.h"

class App {

	public:

		virtual void render() {}

		virtual bool hasNotificationBar() {
			return true;
		}

		bool handleSwipeVertical(int8_t vector);

		virtual bool onSwipeUp() {
			return false;
		}

		virtual bool onSwipeDown() {
			return false;
		}

		virtual bool onSwipeLeft() {
			return false;
		}

		virtual bool onSwipeRight() {
			return false;
		}

		virtual bool handleSwipeHorizontal(int8_t vector);

		virtual bool controlModeIsTouch() {
			return false;
		}

		virtual bool canHandleLongTouch() {
			return false;
		}

		virtual bool handleLongTouch(uint8_t x, uint8_t y) {
			return false;
		}

		virtual bool handleTouch(uint8_t x, uint8_t y) {
			return false;
		}

		virtual bool canBeTouchedLocked() {
			return false;
		}

		virtual void setShouldReRender(bool shouldReRender) {
			this->shouldRerender = shouldReRender;
		}

		bool shouldReRender() {
			return this->shouldRerender;
		}

		void setIsActive(bool isActive) {
			this->isActive = isActive;
		}

		bool getIsActive() {
			return this->isActive;
		}

		void renderTitle(const char *title);

		virtual bool isSystemSleepForbidden() {
			return false;
		}

		virtual uint16_t getAllowedTimeWithoutActivity() {
			return INACTIVITY_TRESHOLD;
		}

		virtual bool handlePEKShort();

	protected:

		bool shouldRerender = true;

		bool isActive = false;

};
