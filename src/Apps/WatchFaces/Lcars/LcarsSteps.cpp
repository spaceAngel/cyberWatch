#include "config.h"
#include "LcarsSteps.h"

#include <LilyGoWatch.h>
#include "UserInterface/UserInterfaceManager.h"

void LcarsSteps::render() {
	TTGOClass::getWatch()->bma->readInterrupt();
	uint stepCount = TTGOClass::getWatch()->bma->getCounter();
	if (
		stepCount != this->prevSteps
		|| this->shouldReRender()
	) {
		TTGOClass::getWatch()->tft->fillRect(142, 23, 80, 50, TFT_BLACK);
		char steps[8];
		(void)snprintf(steps, sizeof(steps), "%d", stepCount);
		TTGOClass::getWatch()->tft->setTextSize(1);
		TTGOClass::getWatch()->tft->setTextColor(TFT_DARKGREY);
		TTGOClass::getWatch()->tft->drawString("STEPS", 142, 26);
		TTGOClass::getWatch()->tft->setTextColor(TFT_PINK);
		TTGOClass::getWatch()->tft->drawString(steps, 147, 52);
		this->setShouldReRender(false);
		this->prevSteps = stepCount;
	}
}