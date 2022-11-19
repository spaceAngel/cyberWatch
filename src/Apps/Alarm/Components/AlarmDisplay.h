#pragma once

#include "UserInterface/Components/Component.h"
#include "Apps/Alarm/AlarmModel.h"

class AlarmDisplay : public Component {

	public:

		void render();

		uint8_t getY();

		AlarmDisplay(uint8_t line) {
			this->line = line;
		};

	protected:

		uint8_t line;

};
