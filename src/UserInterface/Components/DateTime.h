#pragma once

#include "UserInterface/Components/DateTime/Date.h"
#include "UserInterface/Components/DateTime/Time.h"

class DateTime {

	public:

		DateTime() {
			_date = new Date();
			_time = new Time();
		}

		void render();

	protected:

		Date *_date;
		Time *_time;

};
