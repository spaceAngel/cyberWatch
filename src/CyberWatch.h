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
		static CyberWatch *_inst;

		CyberWatch();

		void _handleCabelConnection();

		void _handleEsp32IRQ(bool &PEKshort);

		uint8_t _batteryLowWarnVibrateOnLevel = 101;

		void _handleBatteryLowActions();
		
};


#endif