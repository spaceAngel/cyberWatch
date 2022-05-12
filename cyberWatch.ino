#define LILYGO_WATCH_2020_V3

#define APP_FULL_NAME "CyberWatch 0.1"
#define APP_NAME "CyberWatch"
#define APP_VERSION "0.1"

#include <LilyGoWatch.h>
#include "CyberWatch/CyberWatch.cpp"

void setup() {
	CyberWatch::getInstance()->init();
}

void loop() {
	CyberWatch::getInstance()->loop();
}
