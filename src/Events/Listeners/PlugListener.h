#pragma once

#include "Events/EventListener.h"

class PlugListener : public EventListener {

	public:

		virtual bool listen(uint8_t event);

		virtual void handle();

		PlugListener() {

		}
};
