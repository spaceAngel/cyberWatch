#include "config.h"

#include "Alarm.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"
#include "Core/Hardware/MotorController.h"
#include "UserInterface/Screens/MainScreen.h"
#include "Apps/Alarm/Screens/AlarmSettings.h"
#include "Apps/Alarm/Components/AlarmDisplay.h"
#include "Apps/Alarm/AlarmStorage.h"

void Alarm::render() {
	if (this->shouldReRender()) {
		TTGOClass::getWatch()->tft->drawString(
			"Alarms",
			(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth("Alarms")) / 2,
			28
		);

		this->alarms[0]->render();
		this->alarms[1]->render();
		this->alarms[2]->render();
	}
}

bool Alarm::handleLongTouch(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i <= 2; i++) {
		if (
			y > this->alarms[i]->getY()
			&& y < this->alarms[i]->getY() + 50
		) {
			MainScreen::getInstance()->setAppOnTop(
				new AlarmSettings(i)
			);
		}
	}

	return true;
}

void Alarm::setShouldReRender(bool shouldReRender) {
	for (uint8_t i = 0; i <= Alarm::ALARM_SLOTS; i++) {
		this->alarms[i]->setShouldReRender(shouldReRender);
	}
}

Alarm::Alarm() {
	this->alarms[0] = new AlarmDisplay(0);
	this->alarms[1] = new AlarmDisplay(1);
	this->alarms[2] = new AlarmDisplay(2);
}