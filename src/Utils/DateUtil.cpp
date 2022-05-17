#include "DateUtil.h"

uint8_t DateUtil::weekday(uint year, uint8_t month, uint8_t day) {
	int adjustment, mm, yy;
	if (year < 2000) year += 2000;
	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;
	return (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
}

uint8_t DateUtil::getDaysInMonth(uint year, uint8_t month) {
	switch (month)
	{
		case 1: return 31;
		case 2:
			if (year % 4 == 0) {
				return 29;
			}
			return 28;
		case 3: return 31;
		case 4: return 30;
		case 5: return 31;
		case 6: return 30;
		case 7: return 31;
		case 8: return 31;
		case 9: return 30;
		case 10: return 31;
		case 11: return 30;
		case 12: return 31;
	}
	return 31; //fallback for correct code - program flow never reach this point :-)
}

void DateUtil::monthNameShort(char (&name)[3], uint8_t month) {
	switch (month)
	{
		case 1: strcpy(name, "Jan"); break;
		case 2: strcpy(name, "Feb"); break;
		case 3: strcpy(name, "Mar"); break;
		case 4: strcpy(name, "Apr"); break;
		case 5: strcpy(name, "May"); break;
		case 6: strcpy(name, "Jun"); break;
		case 7: strcpy(name, "Jul"); break;
		case 8: strcpy(name, "Aug"); break;
		case 9: strcpy(name, "Sep"); break;
		case 10: strcpy(name, "Oct"); break;
		case 11: strcpy(name, "Nov"); break;
		case 12: strcpy(name, "Dec"); break;
	}
}
