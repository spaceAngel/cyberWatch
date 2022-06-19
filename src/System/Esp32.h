#pragma once

class Esp32 {

	public:

		static Esp32 *getInstance();

		void initIRQ();

		bool isIRQ();

		void cleanIRQ();
		void setIsIRQ();

		void runWithCpuSpeedHigh(std::function<void(void)> f);

	protected:

		static Esp32 *inst;

		bool IRQ = false;

		Esp32() {
		}

};
