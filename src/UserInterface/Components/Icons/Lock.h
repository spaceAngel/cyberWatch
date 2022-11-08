#pragma once

#include "config.h"

#include "Core/Hardware/BatteryManager.h"
#include "UserInterface/Components/Component.h"

class Lock : public Component{

	public:

		void render();

	protected:

		bool prevState = false;

		const uint POS_X = 195;
		const uint POS_Y = 153;

};
