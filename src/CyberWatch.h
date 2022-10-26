#pragma once

#include "config.h"

#include "Core/RunModes/RunMode.h"

#define RUNMODE_MAIN 0
#define RUNMODE_CHARGING 1

class CyberWatch {

	public:
		static CyberWatch *getInstance();

		void init();

		void loop();

		void setRunMode(uint8_t mode);

	protected:

		static CyberWatch *inst;

		RunMode *runModes[2];
		uint8_t runMode;

		CyberWatch();

};
