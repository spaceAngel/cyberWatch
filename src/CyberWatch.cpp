#include "config.h"

#include <LilyGoWatch.h>
#include <SPIFFS.h>

#include "CyberWatch.h"

#include "Core/Hardware/Display.h"
#include "Core/Hardware/Esp32.h"
#include "Core/Hardware/BatteryManager.h"
#include "Core/Hardware/MoveSensor.h"
#include "Environment/RunAfterCompilation.h"
#include "Environment/SystemInfo.h"
#include "Core/SystemTicker.h"
#include "Events/EventManager.h"
#include "Core/RunModes/MainMode.h"
#include "Core/RunModes/ChargingMode.h"

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
	srand((unsigned)time(NULL));

	TTGOClass::getWatch()->begin();

	#ifdef LILYGO_WATCH_HAS_MOTOR
		TTGOClass::getWatch()->motor_begin();
	#endif

	SPIFFS.begin();
	bool isFirstRun = RunAfterCompilation::handle();
	Display::getInstance()->init();
	BatteryManager::getInstance()->energyConsumptionSavingsSettings();
	Esp32::getInstance()->initIRQ();
	MoveSensor::getInstance()->initIRQ();
	SystemTicker::getInstance();
	SystemInfo::getInstance();
	if (
		BatteryManager::getInstance()->isCharging()
		&& isFirstRun == false
	) {
		this->setRunMode(RUNMODE_CHARGING);
	} else {
		this->setRunMode(RUNMODE_MAIN);
	}
};

void CyberWatch::loop() {
	this->runModes[this->runMode]->loop();
};

void CyberWatch::setRunMode(uint8_t mode) {

	//clear disply
	TTGOClass::getWatch()->tft->fillRect(
		0,
		0,
		TTGOClass::getWatch()->tft->width(),
		TTGOClass::getWatch()->tft->height(),
		COLOR_BACKGROUND
	);

	this->runMode = mode;
	this->runModes[this->runMode]->switchedTo();
}

CyberWatch::CyberWatch() {
	this->runModes[RUNMODE_MAIN] = new MainMode();
	this->runModes[RUNMODE_CHARGING] = new ChargingMode();
}


