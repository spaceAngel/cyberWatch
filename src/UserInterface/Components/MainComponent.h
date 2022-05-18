#pragma once

#include <Arduino.h>

class MainComponent {

	public:

		void setShouldReRender(bool shouldReRender);

		bool shouldReRender();

		virtual void render() {};
		virtual bool handleVerticalSwipe(int8_t vector) {return false;}

	private:

		bool _shouldReRender = true;

};
