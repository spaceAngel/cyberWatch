#pragma once

#include <time.h>

class SystemInfo {

	public:

		static SystemInfo *getInstance();

		uint getUptime();

		protected:

			static SystemInfo *inst;

			time_t startAt;

			SystemInfo();



};

