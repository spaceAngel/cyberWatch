#pragma once

#include "UserInterface/Components/Component.h"

class AlarmSettingsDayButton : public Component {

	public:
		static const uint8_t POS_Y = 162;
		static const uint8_t HEIGHT = 32;

		void render();

		uint8_t getWidth();

		uint8_t getPosX();

		uint8_t getPosY();

		AlarmSettingsDayButton(uint8_t alarm, uint8_t day) {
			this->alarm = alarm;
			this->day = day;
		}

	protected:

		uint8_t day;
		uint8_t alarm;

};
