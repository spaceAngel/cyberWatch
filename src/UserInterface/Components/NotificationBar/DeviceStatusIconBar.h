#pragma once

#define DEVICESTATE_NOTIFICATIONS_CHARGING 1
#define DEVICESTATE_NOTIFICATIONS_DISPLAY_ALWAYS_ON 2
#define DEVICESTATE_NOTIFICATIONS_STOPWATCH_RUNNING 4
#define DEVICESTATE_NOTIFICATIONS_DISPLAY_LOCKED 8

#include "UserInterface/Icons/IconStruct.h"
#include "UserInterface/Components/Component.h"

class DeviceStatusIconBar : public Component {

	public:

		void render();

	protected:

		uint8_t prevBits = 0;

		void renderIcon(IconStruct icon, uint8_t &pos);

		uint8_t getDeviceStateBitMask();

		void renderIconCharging(uint8_t &pos);
		void renderIconDisplayAlwaysOn(uint8_t &pos);
		void renderIconStopwatchRunning(uint8_t &pos);
		void renderIconDisplayLocked(uint8_t &pos);

};
