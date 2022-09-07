#include "config.h"

#include "SettingsPanel.h"
#include "UserInterface/UserInterfaceManager.h"
#include "UserInterface/Icons/LightBulb.h"
#include "Environment/AppSettings.h"

#include <LilyGoWatch.h>

#include "System/Esp32.h"

void SettingsPanel::render() {
	if (
		this->lastMask != AppSettings::getInstance()->getSettingsByteMask()
		|| this->shouldReRender()
	) {

		Esp32::getInstance()->runWithCpuSpeedHigh(
			[this]() {
				for (int32_t i = 0; i <= BUTTONS; i++) {
					this->buttons[i]->render();
				}
			}
		);
		this->setShouldReRender(false);
		this->lastMask = AppSettings::getInstance()->getSettingsByteMask();
	}
}

bool SettingsPanel::handlePEKShort() {
	return false;
}

bool SettingsPanel::controlModeIsTouch() {
	return true;
}

bool SettingsPanel::handleTouch(uint8_t x, uint8_t y) {
	for (int32_t i = 0; i <= BUTTONS; i++) {
		if (
			(x > this->buttons[i]->getX())
			&& (x < this->buttons[i]->getX() + this->buttons[i]->getWidth())
			&& (y > this->buttons[i]->getY())
			&& (y < this->buttons[i]->getY() + this->buttons[i]->getHeight())
		) {
			this->buttons[i]->handleTouch();
		}
	}
	return false;
}

void SettingsPanel::setShouldReRender(bool shouldReRender) {
	for (int32_t i = 0; i <= BUTTONS; i++) {
		this->buttons[i]->setShouldReRender(shouldReRender);
	}
}
