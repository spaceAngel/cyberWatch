#pragma once

class MoveSensor {

	public:

		static MoveSensor *getInstance();

		void initIRQ();

		void cleanIRQ();

		void setIsIRQ();

		bool isTilt();

	protected:

		static MoveSensor *_inst;

		bool _IRQ = false;

		MoveSensor();

};
