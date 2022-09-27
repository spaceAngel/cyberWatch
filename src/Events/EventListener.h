#pragma once

#include <Arduino.h>

class EventListener {

	public:

		virtual bool listen(uint8_t event);

		virtual void handle();
};
