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
		DateTime();

	protected:

		Date *_date;
		Time *_time;
		AnalogClocks *_clocks;
		Planetoid *_planetoid;
		DigitalClocks *_digital;

		const uint8_t FACE_DIGITAL = 1;
		const uint8_t FACE_ANALOG = 2;
		const uint8_t FACE_PLANETOID = 3;

		const uint8_t FACES = 3;

		uint _currentFace = FACE_PLANETOID;

};
