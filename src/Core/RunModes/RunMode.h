#pragma once

#include "UserInterface/Apps/StopWatch.h"

class RunMode {

	public:

		virtual void switchedTo() {};

		virtual void loop() {};

};
