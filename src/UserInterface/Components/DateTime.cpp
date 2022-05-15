#include "config.h"

#include "DateTime.h"

void DateTime::render() {
	_date->render();
	_time->render();
};
