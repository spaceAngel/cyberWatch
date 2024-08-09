#pragma once

#include <Arduino.h>

#include "UserInterface/App.h"
#include "Apps/WatchFaces/WatchFace.h"
#include "Apps/WatchFaces/AnalogClocks.h"
#include "Apps/WatchFaces/DigitalClocks.h"
#include "Apps/WatchFaces/ProgressBars.h"
#include "Apps/WatchFaces/NeonCircles.h"
#include "Apps/WatchFaces/SensorGrid.h"
#include "Apps/WatchFaces/KnightRider.h"
#include "Apps/WatchFaces/Vaporwave.h"
#include "Apps/WatchFaces/InfoPanel/InfoPanel.h"
#include "Apps/WatchFaces/Lcars.h"
#include "Apps/WatchFaces/LogoFace.h"

class Watches : public App {

	public:

		bool handleSwipeHorizontal(int8_t vector);
		void setShouldReRender(bool shouldReRender);
		WatchFace *getCurrentFace();
		void render();


		bool handlePEKShort();

		Watches();

		bool hasNotificationBar();

		bool canHandleLongTouch() {
			return true;
		}

		bool handleLongTouch(uint8_t x, uint8_t y);

	protected:

		const int FACES = 8;

		WatchFace *clockFaces[9];
		int8_t currentFace = 6;

		InfoPanel *infoPanel;

		void createFaces() {
			clockFaces[0] = new DigitalClocks();
			clockFaces[1] = new AnalogClocks();
			clockFaces[2] = new LogoFace();
			clockFaces[3] = new ProgressBars();
			clockFaces[4] = new NeonCircles();
			clockFaces[5] = new SensorGrid();
			clockFaces[6] = new KnightRider();
			clockFaces[7] = new Vaporwave();
			clockFaces[8] = new Lcars();

		}

};
