#pragma once

#include <Arduino.h>

#include "UserInterface/Components/Component.h"

class LcarsSteps : public Component {
	public:
		void render();

		LcarsSteps() {};

	protected:
		uint16_t prevSteps = 0;

};
