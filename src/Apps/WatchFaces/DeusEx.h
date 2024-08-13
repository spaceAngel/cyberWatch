#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "Apps/WatchFaces/WatchFace.h"

#define DEUSEX_DEVICESTATE_LOCKED 1
#define DEUSEX_DEVICESTATE_DISPLAYON 2;
#define DEUSEX_DEVICESTATE_ALARM 4;

class DeusEx : public WatchFace {

	public:
		void render();

		bool hasToolbar() {
			return false;
		}

		bool hasInfoPanel() {
			return false;
		}

		DeusEx() {}

	protected:
		const uint8_t ICONS_POS_Y = 27;
		uint8_t prevMinute = 99;
		uint8_t prevBattery = 99;
		bool prevCabelPlugged = false;

		uint8_t prevBitMask;

		void renderTime();
		void renderDate();

		void renderDeviceStateIcons();
		void renderBatteryInfo();

		uint8_t getDeviceStateBitMask();


};
