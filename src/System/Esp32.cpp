#include "config.h"

#include <LilyGoWatch.h>

#include "Esp32.h"

Esp32* Esp32::_inst;

Esp32 *Esp32::getInstance() {
	if (Esp32::_inst == nullptr) {
		Esp32::_inst = new Esp32();
	}
	return Esp32::_inst;
}

void Esp32::initIRQ() {
	pinMode(AXP202_INT, INPUT_PULLUP);
	attachInterrupt(
		AXP202_INT,
		[] {
			Esp32::getInstance()->setIsIRQ();
		},
		FALLING
	);
	TTGOClass::getWatch()->power->enableIRQ(
		AXP202_PEK_SHORTPRESS_IRQ | AXP202_PEK_LONGPRESS_IRQ |
		AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ |
		AXP202_ACIN_REMOVED_IRQ | AXP202_ACIN_CONNECT_IRQ,
		true
	);
	TTGOClass::getWatch()->power->clearIRQ();
	pinMode(TOUCH_INT, INPUT);
}

bool Esp32::isIRQ() {
	return _IRQ;
}

void Esp32::cleanIRQ() {
	_IRQ = false;
	TTGOClass::getWatch()->power->clearIRQ();
}

void Esp32::setIsIRQ() {
	_IRQ = true;
}
