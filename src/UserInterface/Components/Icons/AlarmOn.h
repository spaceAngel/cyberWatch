#pragma once

#include "config.h"

#include "Core/Hardware/BatteryManager.h"
#include "UserInterface/Components/Component.h"

class AlarmOn : public Component {

	public:

		void render();

	protected:

		const uint8_t POS_X = 155;
		const uint8_t POS_Y = 180;

		bool prevState = false;
};