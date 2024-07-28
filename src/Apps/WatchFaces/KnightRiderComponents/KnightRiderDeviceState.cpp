#include "config.h"

#include "KnightRiderDeviceState.h"

#include <LilyGoWatch.h>

#include "Core/Hardware/Display.h"

#include "Apps/StopWatch/StopWatchRegistry.h"
#include "Environment/AppSettings.h"
#include "UserInterface/UserInterfaceManager.h"

void KnightRiderDeviceState::render() {
	uint8_t bitmask = this->getDeviceStateBitMask();
	if (
		this->shouldReRender() == true
		|| this->prevBitMask != bitmask
	) {
		this->renderButton(1, "LCK", UserInterfaceManager::getInstance()->isLocked());
		this->renderButton(2, "STP", StopWatchRegistry::getInstance()->getRunning());
		this->renderButton(3, "DSP", AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON));
		this->prevBitMask = bitmask;
	}
	this->setShouldReRender(false);
}

void KnightRiderDeviceState::renderButton(uint8_t col, const char* text, bool state) {
	uint8_t displayWidth = TTGOClass::getWatch()->tft->width() - 30;
	uint8_t buttonWidth = displayWidth / 3;
	TTGOClass::getWatch()->tft->setTextFont(1);
	TTGOClass::getWatch()->tft->setTextSize(3);
	TTGOClass::getWatch()->tft->fillRect(
		15 + buttonWidth * (col - 1),
		POS_Y,
		TTGOClass::getWatch()->tft->textWidth(text) + 10,
		TTGOClass::getWatch()->tft->fontHeight() + 8,
		state ? TFT_YELLOW : TFT_BLACK
	);

	TTGOClass::getWatch()->tft->setTextColor(
		state ? TFT_BLACK : TFT_RED
	);
	TTGOClass::getWatch()->tft->drawString(
		text,
		15 + buttonWidth * (col - 1) + ((buttonWidth - TTGOClass::getWatch()->tft->textWidth(text)) / 2),
		POS_Y + 5
	);

	Display::getInstance()->resetTypographySettings();
}


uint8_t KnightRiderDeviceState::getDeviceStateBitMask() {
	uint8_t bits = 0;
	if (StopWatchRegistry::getInstance()->getRunning()) {
		bits |= KNIGHTRIDER_DEVCIESTATE_STOPWATCH_RUNNING;
	}

	if (AppSettings::getInstance()->get(APPSETTINGS_ALWAYS_ON)) {
		bits |= KNIGHTRIDER_DEVCIESTATE_DISPLAYON;
	}

	if (UserInterfaceManager::getInstance()->isLocked() == true) {
		bits |= KNIGHTRIDER_DEVCIESTATE_LOCKED;
	}

	return bits;
}