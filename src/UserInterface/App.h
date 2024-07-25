#pragma once

#define APP_POSITION_TOP 28

#include <Arduino.h>

class App {

	public:

		virtual void render() {}

		virtual bool hasNotificationBar() {
			return true;
		}

		virtual bool handleSwipeVertical(int8_t vector) {
			return false;
		}

		virtual bool handleSwipeHorizontal(int8_t vector) {
			return false;
		}

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

		virtual bool handlePEKShort();

	protected:

		bool shouldRerender = true;

		bool isActive = false;

};
