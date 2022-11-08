#pragma once

class App {

	public:

		virtual void render() {}

		virtual bool hasNotificationBar() {
			return true;
		}

		virtual bool handleSwipeVertical(int8_t vector) {
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

		virtual bool isSystemSleepForbidden() {
			return false;
		}

		virtual bool handlePEKShort() {
			return false;
		};

	protected:

		bool shouldRerender = true;

		bool isActive = false;

};
