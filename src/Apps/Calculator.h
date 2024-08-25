#pragma once

#include <Arduino.h>

#include "UserInterface/App.h"

#define OPERAND_PLUS 0
#define OPERAND_MINUS 1
#define OPERAND_MULTIPLE 2
#define OPERAND_DIVIDE 3

class Calculator : public App {

	public:


		void render();
		Calculator() {};

		virtual uint16_t getAllowedTimeWithoutActivity() {
			return 100;
		}

		virtual bool hasNotificationBar() {
			return false;
		}

		bool controlModeIsTouch() {
			return true;
		}

		bool handleTouch(uint8_t x, uint8_t y);

	protected:

		double currentNumber = 0;
		double prevNumber = NULL;
		uint8_t decimalCharCaret = 0;
		uint8_t operand = NULL;

		double prevDisplayedNumber = 0;

		bool wasExecuted = false;

		void renderKeyboard();
		void renderDisplay();
		void renderClearButton();
		void numberPressed(double number);
		void operandPressed(uint8_t operand);
		void executePressed();
		void clearPressed();


		void renderButton(
			uint8_t x,
			uint8_t y,
			char* symbol,
			bool background
		);



};
