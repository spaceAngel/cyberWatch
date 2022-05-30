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

uint8_t DateUtil::getDaysInMonth(uint year, uint8_t month) {
	uint8_t rslt;
	switch (month) {
		case 1: rslt = 31; break;
		case 2: rslt = ((year % 4) == 0) ? 29 : 28; break;
		case 3: rslt = 31; break;
		case 4: rslt = 30; break;
		case 5: rslt = 31; break;
		case 6: rslt = 30; break;
		case 7: rslt = 31; break;
		case 8: rslt = 31; break;
		case 9: rslt = 30; break;
		case 10: rslt = 31; break;
		case 11: rslt = 30; break;
		case 12: rslt = 31; break;
		default: rslt = 31; break; //fallback for correct code - program flow never reach this point :-)
	}
	return rslt;
}

void DateUtil::monthNameShort(char (&name)[4], uint8_t month) {
	switch (month)
	{
		case 1: (void)strcpy(name, "Jan"); break;
		case 2: (void)strcpy(name, "Feb"); break;
		case 3: (void)strcpy(name, "Mar"); break;
		case 4: (void)strcpy(name, "Apr"); break;
		case 5: (void)strcpy(name, "May"); break;
		case 6: (void)strcpy(name, "Jun"); break;
		case 7: (void)strcpy(name, "Jul"); break;
		case 8: (void)strcpy(name, "Aug"); break;
		case 9: (void)strcpy(name, "Sep"); break;
		case 10: (void)strcpy(name, "Oct"); break;
		case 11: (void)strcpy(name, "Nov"); break;
		case 12: (void)strcpy(name, "Dec"); break;
		default:break; //fallback for correct code - program flow never reach this point :-)
	}
}
