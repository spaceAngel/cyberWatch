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
