#include "config.h"

class RunningStopWatch {

	public:

		void render();

	protected:

		const uint8_t POS_X = 180;
		const uint8_t POS_Y = 180;

		bool wasRunning = false;

		void clear();

};
