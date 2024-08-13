#pragma once

#include <Arduino.h>

#define BACKGROUND_LOGO 1
#define BACKGROUND_WATCH_VAPORWAVE 2
#define BACKGROUND_WATCH_LCARS 3
#define BACKGROUND_WATCH_ANALOG 4
#define BACKGROUND_WATCH_DEUSEX 5

class BackgroundRenderer {

	public:

		static void renderImage(uint8_t image);

		static void renderImage(uint8_t image, uint8_t x,uint8_t y);

};
