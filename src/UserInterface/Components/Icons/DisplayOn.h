#pragma once

#include "config.h"

#include "Core/Hardware/BatteryManager.h"
#include "UserInterface/Components/MainComponent.h"

class DisplayOn : public MainComponent{

	public:

		void render();

	protected:

		bool prevState = false;

		const uint POS_X = 170;
		const uint POS_Y = 153;

};
