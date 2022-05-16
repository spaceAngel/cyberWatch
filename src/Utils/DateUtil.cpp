#include "DateUtil.h"

uint8_t DateUtil::weekday(uint year, uint8_t month, uint8_t day) {
	int adjustment, mm, yy;
	if (year < 2000) year += 2000;
	adjustment = (14 - month) / 12;
	mm = month + 12 * adjustment - 2;
	yy = year - adjustment;
	return (day + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
}