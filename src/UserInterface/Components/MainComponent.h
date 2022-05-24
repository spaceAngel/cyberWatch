#pragma once

#include <Arduino.h>

class MainComponent {

	public:

		virtual void setShouldReRender(bool shouldReRender);

		bool shouldReRender();

		virtual void render() {};
		virtual bool handleVerticalSwipe(int8_t vector) {return false;}
		virtual bool handlePEKShort() {return false;};

	private:

		bool _shouldReRender = true;

};
