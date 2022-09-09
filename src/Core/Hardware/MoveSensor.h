#pragma once

class MoveSensor {

	public:

		static MoveSensor *getInstance();

		void initIRQ();

		void cleanIRQ();

		void setIsIRQ();

		bool isTilt();

	protected:

		static MoveSensor *inst;

		bool IRQ = false;

		MoveSensor();

};
