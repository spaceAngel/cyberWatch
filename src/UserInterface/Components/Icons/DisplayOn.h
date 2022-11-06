#pragma once

#include "config.h"

#include "Core/Hardware/BatteryManager.h"
#include "UserInterface/Components/Component.h"

class DisplayOn : public Component{

	public:

		void render();

	protected:

		bool prevState = false;

		const uint POS_X = 170;
		const uint POS_Y = 153;

};
