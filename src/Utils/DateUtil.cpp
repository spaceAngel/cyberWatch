#include "DateUtil.h"

uint8_t DateUtil::weekday(uint year, uint8_t month, uint8_t day) {
	int adjustment;
	int mm = month;
	int yy = year;
	int dd = day;
	if (year < 2000) {yy += 2000;}
	adjustment = (14 - mm) / 12;
	mm += ((12 * adjustment)) - 2;
	yy = yy - adjustment;
	return (dd + (
			(
				(
					(
						(
							(
								(
									(13 * mm) - 1
								)
								/ 5
							) + yy
						) + (yy / 4)
					)
					- (yy / 100)
				)
				+ (yy / 400)
			)
		)
	) % 7;
}

uint8_t DateUtil::getDaysInMonth(uint year, int month) {
	uint8_t rslt = 0;
	const uint8_t daysInMonth[12] = {
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	if ((month >= 1) && (month <= 12)) {
		if ((month == 2) && ((year % 4) == 0)) {
			rslt = 29;
		} else {
			rslt = daysInMonth[month - 1];
		}
	}
	return rslt;
}

void DateUtil::monthNameShort(char (&name)[4], int month) {
	const char * months[12] = {
		"Jan", "Feb", "Mar",
		"Apr", "May", "Jun",
		"Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec"
	};
	if ((month >= 1) && (month <= 12)) {
		(void)strcpy(name, months[month - 1]);
	}

}

// calculation of weekday used from here https://forum.arduino.cc/t/rtc-clock-with-days-of-week/426045/4
void DateUtil::weekdayName(char *dayInWeekStr, uint year, uint8_t month, uint8_t day) {
	uint8_t dayInWeek = DateUtil::weekday(year, month, day);
	switch (dayInWeek) {
		case 0: (void)strcpy(dayInWeekStr, "Sunday"); break;
		case 1: (void)strcpy(dayInWeekStr, "Monday"); break;
		case 2: (void)strcpy(dayInWeekStr, "Tuesday"); break;
		case 3: (void)strcpy(dayInWeekStr, "Wednesday"); break;
		case 4: (void)strcpy(dayInWeekStr, "Thursday"); break;
		case 5: (void)strcpy(dayInWeekStr, "Friday"); break;
		case 6: (void)strcpy(dayInWeekStr, "Saturday"); break;
	}
}

// calculation of weekday used from here https://forum.arduino.cc/t/rtc-clock-with-days-of-week/426045/4
void DateUtil::weekdayNameShort(char *dayInWeekStr, uint year, uint8_t month, uint8_t day) {
	uint8_t dayInWeek = DateUtil::weekday(year, month, day);
	switch (dayInWeek) {
		case 0: (void)strcpy(dayInWeekStr, "Sun"); break;
		case 1: (void)strcpy(dayInWeekStr, "Mon"); break;
		case 2: (void)strcpy(dayInWeekStr, "Tue"); break;
		case 3: (void)strcpy(dayInWeekStr, "Wed"); break;
		case 4: (void)strcpy(dayInWeekStr, "Thu"); break;
		case 5: (void)strcpy(dayInWeekStr, "Fri"); break;
		case 6: (void)strcpy(dayInWeekStr, "Sat"); break;
	}
}