#pragma once

#include "Apps/WatchFaces/WatchFace.h"
#include "Apps/WatchFaces/KnightRiderComponents/KnightRiderButton.h"
#include "Apps/WatchFaces/KnightRiderComponents/KnightRiderSpeaker.h"
#include "Apps/WatchFaces/KnightRiderComponents/KnightRiderBatteryBar.h"
#include "Apps/WatchFaces/KnightRiderComponents/KnightRiderDeviceState.h"

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
