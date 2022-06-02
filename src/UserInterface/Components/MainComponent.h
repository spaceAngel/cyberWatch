#pragma once

#include <Arduino.h>

class MainComponent {

	public:

		virtual void setShouldReRender(bool shouldReRender);

		bool shouldReRender();

		virtual void render() {};

		virtual bool handleSwipeVertical(int8_t vector) {
			return false;
		}

		virtual bool handlePEKShort() {return false;};
		void setIsActive(bool active);
		bool getIsActive();
		virtual bool isSystemSleepForbidden() {
			return false;
		}

	private:

		bool shouldRerender = true;

		bool isActive = false;

};
