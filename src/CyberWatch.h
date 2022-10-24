#pragma once

#include "config.h"

#include "Core/RunModes/RunMode.h"

#define RUNNMODE_MAIN 0

class CyberWatch {

	public:
		static CyberWatch *getInstance();

		void init();

		void loop();

		void setRunMode(uint8_t mode);

	protected:

		static CyberWatch *inst;

		RunMode *runModes[1];
		uint8_t runMode;

		CyberWatch();

};
