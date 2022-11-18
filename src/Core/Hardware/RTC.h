#pragma once

#include <LilyGoWatch.h>

class RTC {

	public:

		static RTC *getInstance();

		RTC_Date getCurrentDate();

		void updateDate();


	protected:

		static RTC *inst;

		RTC_Date lastDateTime;

		RTC();

};
