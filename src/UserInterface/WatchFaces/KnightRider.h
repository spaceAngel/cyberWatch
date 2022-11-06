#pragma once

#include "UserInterface/WatchFaces/WatchFace.h"
#include "UserInterface/WatchFaces/KnightRiderComponents/KnightRiderButton.h"
#include "UserInterface/WatchFaces/KnightRiderComponents/KnightRiderSpeaker.h"
#include "UserInterface/WatchFaces/KnightRiderComponents/KnightRiderBatteryBar.h"
#include "UserInterface/WatchFaces/KnightRiderComponents/KnightRiderDeviceState.h"

class KnightRider : public WatchFace {

	public:

		void render();
		void setShouldReRender(bool shouldReRender);

		KnightRider();

	protected:

		KnightRiderButton *buttons[6];
		KnightRiderSpeaker *speaker;
		KnightRiderBatteryBar *batteryBar;
		KnightRiderDeviceState *deviceBar;

		void renderDataCells();

		void renderBattery(uint8_t capacity);


};
