#pragma once

#include "Events/EventListener.h"

class AlarmListener : public EventListener {

	public:

		virtual bool listen(uint8_t event);

		virtual void handle();

		AlarmListener() {}

	protected:

		uint8_t prevMinute = 99;
};
