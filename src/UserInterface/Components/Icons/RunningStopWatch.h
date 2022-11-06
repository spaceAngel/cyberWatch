#include "config.h"

#include "UserInterface/Components/Component.h"

class RunningStopWatch : public Component {

	public:

		void render();

	protected:

		const uint8_t POS_X = 180;
		const uint8_t POS_Y = 180;

		bool wasRunning = false;

		void clear();

};
