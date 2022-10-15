#pragma once

#include <time.h>

class SystemInfo {

	public:

		static SystemInfo *getInstance();

		uint getUptime();

		void setPlugState(bool state);

		bool getPluggedIn();

		uint getUnplugTime();

		protected:

			static SystemInfo *inst;

			time_t startAt;

			bool pluggedIn = false;

			time_t pluggedInAt;

			SystemInfo();



};

