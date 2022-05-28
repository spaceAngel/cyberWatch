#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/DateTime/AnalogClocks.h"
#include "UserInterface/Components/MainPanel/DateTime/Planetoid.h"
#include "UserInterface/Components/MainPanel/DateTime/DigitalClocks.h"

class DateTime : public MainComponent {

	public:

		bool handleVerticalSwipe(int8_t vector);
		void setShouldReRender(bool shouldReRender);
		MainComponent *getCurrentFace();
		void render();

		DateTime() {
			_clockFaces[0] = new DigitalClocks();
			_clockFaces[1] = new AnalogClocks();
			_clockFaces[2] = new Planetoid();
		};

	protected:

		const int FACES = 2;

		MainComponent *_clockFaces[3];
		int8_t _currentFace = 2;

};
