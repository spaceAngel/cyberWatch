#pragma once

class MoveSensor {

	public:

		static MoveSensor *getInstance();

		void initIRQ();

		void cleanIRQ();

		void setIsIRQ();

		bool isTilt();

		uint16_t getStepsCount();

		uint8_t getDirection();

	protected:

		static MoveSensor *inst;

		bool IRQ = false;

		MoveSensor();

};
