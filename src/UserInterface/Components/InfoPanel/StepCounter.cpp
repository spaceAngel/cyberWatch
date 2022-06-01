#include "config.h"
#include "StepCounter.h"

#include <LilyGoWatch.h>
#include "UserInterface/Icons/FootPrints.h"

void StepCounter::render() {
	if (iconIsRendered == false) {
		TTGOClass::getWatch()->tft->setSwapBytes(true);
		TTGOClass::getWatch()->tft->pushImage(POS_X + 7, POS_Y, 22, 22, iconFootPrints);
		iconIsRendered = true;
	}
	TTGOClass::getWatch()->bma->readInterrupt();
	uint stepCount = TTGOClass::getWatch()->bma->getCounter();

	if (stepCount != this->prevStepCount) {
		this->clearDisplay();
		char steps[8];
		(void)snprintf(
			steps,
			sizeof(steps),
			"%d",
			stepCount
		);

		TTGOClass::getWatch()->tft->drawString(steps, (int32_t)POS_X + 43, (int32_t)POS_Y + 1);
		this->prevStepCount = stepCount;
	}
}


void StepCounter::clearDisplay() {
	TTGOClass::getWatch()->tft->fillRect(
		(int32_t)POS_X + 44,
		(int32_t)POS_Y,
		100,
		TTGOClass::getWatch()->tft->fontHeight(),
		COLOR_BACKGROUND
	);
}
