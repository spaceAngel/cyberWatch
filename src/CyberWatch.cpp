#include "config.h"

#include <LilyGoWatch.h>
#include <SPIFFS.h>

#include "CyberWatch.h"

#include "Core/Hardware/Display.h"
#include "Core/Hardware/Esp32.h"
#include "Core/Hardware/BatteryManager.h"
#include "Core/Hardware/MoveSensor.h"
#include "Core/Hardware/MotorController.h"
#include "Environment/RunAfterCompilation.h"
#include "Environment/SystemInfo.h"
#include "Core/SystemTicker.h"
#include "Events/EventManager.h"
#include "Core/RunModes/MainMode.h"

CyberWatch* CyberWatch::inst;

CyberWatch *CyberWatch::getInstance() {
	if (CyberWatch::inst == nullptr) {
CyberWatch::inst = new CyberWatch();
	}
	return CyberWatch::inst;
}

void CyberWatch::init() {

	Serial.begin(SERIAL_RATE);
	Serial.println("cyberWatch starting");

	TTGOClass::getWatch()->begin();

	#ifdef LILYGO_WATCH_HAS_MOTOR
		TTGOClass::getWatch()->motor_begin();
	#endif

	SPIFFS.begin();
	RunAfterCompilation::handle();
	Display::getInstance()->init();
	BatteryManager::getInstance()->energyConsumptionSavingsSettings();
	Esp32::getInstance()->initIRQ();
	MoveSensor::getInstance()->initIRQ();
	SystemTicker::getInstance();
	SystemInfo::getInstance();
	this->setRunMode(RUNNMODE_MAIN);
};

void CyberWatch::loop() {
	this->runModes[this->runMode]->loop();
};

void CyberWatch::setRunMode(uint8_t mode) {
	this->runMode = mode;
	this->runModes[this->runMode]->switchedTo();
}

CyberWatch::CyberWatch() {
	this->runModes[0] = new MainMode();
}


