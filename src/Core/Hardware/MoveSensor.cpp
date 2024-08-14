#include "config.h"

#include <LilyGoWatch.h>

#include "MoveSensor.h"

MoveSensor* MoveSensor::inst;

MoveSensor *MoveSensor::getInstance() {
	if (MoveSensor::inst == nullptr) {
		MoveSensor::inst = new MoveSensor();
	}
	return MoveSensor::inst;
}

void MoveSensor::initIRQ() {
	Acfg cfg;
	cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
	cfg.range = BMA4_ACCEL_RANGE_2G;
	cfg.bandwidth = BMA4_ACCEL_RES_AVG64;
	cfg.perf_mode = BMA4_CONTINUOUS_MODE;
	TTGOClass::getWatch()->bma->accelConfig(cfg);
	TTGOClass::getWatch()->bma->enableAccel();
	pinMode(BMA423_INT1, INPUT);
	attachInterrupt(
		BMA423_INT1,
		[] {
			MoveSensor::getInstance()->setIsIRQ();
		},
		RISING
	); //It must be a rising edge
	TTGOClass::getWatch()->bma->enableFeature(BMA423_STEP_CNTR, true);
	TTGOClass::getWatch()->bma->enableFeature(BMA423_TILT, true);
	TTGOClass::getWatch()->bma->enableTiltInterrupt();
	TTGOClass::getWatch()->bma->enableWakeupInterrupt();
	}

void MoveSensor::cleanIRQ() {
	this->IRQ = false;
	TTGOClass::getWatch()->power->clearIRQ();
}

void MoveSensor::setIsIRQ() {
	this->IRQ = true;
}

bool MoveSensor::isTilt() {
	bool isTilt = false;
	if (this->IRQ) {
		TTGOClass::getWatch()->bma->readInterrupt();
		MoveSensor::getInstance()->cleanIRQ();
		isTilt = true;
	}
	return isTilt;
}

uint16_t MoveSensor::getStepsCount() {
	return TTGOClass::getWatch()->bma->getCounter();
}

uint8_t MoveSensor::getDirection() {
	return TTGOClass::getWatch()->bma->direction();
}

Accel MoveSensor::getAccel() {
	Accel acc;
	TTGOClass::getWatch()->bma->getAccel(acc);
	return acc;
}

MoveSensor::MoveSensor() {
}
