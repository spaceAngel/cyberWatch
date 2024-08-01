#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class LcarsSteps : public Component {
	public:
		void render();

		LcarsSteps() {};

	protected:
		uint8_t prevSteps = 0;

};
