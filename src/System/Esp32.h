#pragma once

class Esp32 {

	public:

		static Esp32 *getInstance();

		void initIRQ();

		bool isIRQ();

		void cleanIRQ();
		void setIsIRQ();

	protected:

		static Esp32 *_inst;

		bool _IRQ = false;

		Esp32() {
		}

};
