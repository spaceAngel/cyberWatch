#ifndef CYBERWATCH
#define CYBERWATCH

#include "config.h"

class CyberWatch {

	public:
		static CyberWatch *getInstance();

		void init();

		void loop();

		void turnOff();
	protected:
		static CyberWatch *inst;

		CyberWatch();

		void handleCabelConnection();

		void handleEsp32IRQ(bool &PEKshort);

		uint8_t batteryLowWarnVibrateOnLevel = 101;

		void handleBatteryLowActions();

};


#endif