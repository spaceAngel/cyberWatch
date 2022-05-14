#include "config.h"

#include <LilyGoWatch.h>
#include "CyberWatch.h"

void setup() {
	CyberWatch::getInstance()->init();
}

void loop() {
	CyberWatch::getInstance()->loop();
}
