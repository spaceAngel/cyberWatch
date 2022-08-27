#pragma once

#include <Arduino.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/WatchFaces/AnalogClocks.h"
#include "UserInterface/Components/MainPanel/WatchFaces/Planetoid.h"
#include "UserInterface/Components/MainPanel/WatchFaces/DigitalClocks.h"
#include "UserInterface/Components/MainPanel/WatchFaces/ProgressBars.h"
#include "UserInterface/Components/MainPanel/WatchFaces/NeonCircles.h"

class DateTime : public MainComponent {

	public:

		bool handleSwipeVertical(int8_t vector);
		void setShouldReRender(bool shouldReRender);
		MainComponent *getCurrentFace();
		void render();
		bool handlePEKShort();

		DateTime();

	protected:

		const int FACES = 4;

		MainComponent *clockFaces[5];
		int8_t currentFace = 4;

		void createFaces() {
			clockFaces[0] = new DigitalClocks();
			clockFaces[1] = new AnalogClocks();
			clockFaces[2] = new Planetoid();
			clockFaces[3] = new ProgressBars();
			clockFaces[4] = new NeonCircles();
		}

};
