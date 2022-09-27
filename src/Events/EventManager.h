#pragma once

#include <Arduino.h>
#include "Events/EventListener.h"
#include "Events/Listeners/PlugListener.h"

#define EVENT_CABLE_PLUG 1
#define EVENT_CABLE_UNPLUG 2

class EventManager {

	public:

		static EventManager *getInstance();

		void fireEvent(uint8_t event);

	protected:

		static EventManager *inst;

		uint8_t listenersCount = 1;

		EventListener *listeners[1];

		EventManager() {
			this->listeners[0] = new PlugListener();
		}
};
