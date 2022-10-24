#pragma once

#include "UserInterface/Components/MainPanel/StopWatch.h"

class RunMode {

	public:

		virtual void switchedTo() {};

		virtual void loop() {};

};
