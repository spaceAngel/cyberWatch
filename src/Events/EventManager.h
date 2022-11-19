#pragma once

#include <Arduino.h>
#include "Events/EventListener.h"
#include "Events/Listeners/PlugListener.h"
#include "Events/Listeners/BatteryLeveLWarningsListener.h"
#include "Apps/Alarm/AlarmListener.h"

#define EVENT_CABLE_PLUG 1
#define EVENT_CABLE_UNPLUG 2
#define EVENT_BATTERY_CHANGE 3
#define EVENT_TIME_CHANGE 4

class EventManager {

	public:

		static EventManager *getInstance();

		void fireEvent(uint8_t event);

	protected:

		static EventManager *inst;

		uint8_t listenersCount = 3;

		EventListener *listeners[3];

		EventManager() {
			this->listeners[0] = new PlugListener();
			this->listeners[1] = new BatteryLeveLWarningsListener();
			this->listeners[2] = new AlarmListener();
		}
};

