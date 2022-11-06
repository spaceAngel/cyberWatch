#include "config.h"

#include <LilyGoWatch.h>

#include "KnightRider.h"
#include "Core/Hardware/RTC.h"
#include "UserInterface/WatchFaces/KnightRiderComponents/KnightRiderButton.h"
#include "UserInterface/WatchFaces/KnightRiderComponents/KnightRiderDeviceState.h"
#include "UserInterface/WatchFaces/KnightRiderComponents/KnightRiderSpeaker.h"
#include "Core/Hardware/BatteryManager.h"

void KnightRider::render() {
	uint8_t cellWidth = 24;
	uint8_t cellHeight = 12;

	this->renderDataCells();
	this->batteryBar->render();
	this->deviceBar->render();

	this->speaker->render();
}

void KnightRider::setShouldReRender(bool shouldReRender) {
	MainComponent::setShouldReRender(shouldReRender);
	for (uint8_t i = 0; i<= 5; i++) {
		this->buttons[i]->setShouldReRender(shouldReRender);
	}
	this->batteryBar->setShouldReRender(shouldReRender);
}

void KnightRider::renderDataCells() {
	RTC_Date currentTime = RTC::getInstance()->getCurrentDate();
	this->buttons[0]->render(currentTime.hour);
	this->buttons[1]->render(currentTime.minute);
	this->buttons[2]->render(currentTime.second);
	this->buttons[3]->render(currentTime.day);
	this->buttons[4]->render(currentTime.month);
	this->buttons[5]->render(currentTime.year % 2000);
}

KnightRider::KnightRider() {
	this->buttons[0] = new KnightRiderButton(1, 1, TFT_YELLOW);
	this->buttons[1] = new KnightRiderButton(2, 1, TFT_YELLOW);
	this->buttons[2] = new KnightRiderButton(3, 1, TFT_ORANGE);
	this->buttons[3] = new KnightRiderButton(1, 2, TFT_YELLOW);
	this->buttons[4] = new KnightRiderButton(2, 2, TFT_YELLOW);
	this->buttons[5] = new KnightRiderButton(3, 2, TFT_ORANGE);
	this->speaker = new KnightRiderSpeaker();
	this->batteryBar = new KnightRiderBatteryBar();
	this->deviceBar = new KnightRiderDeviceState();
}
