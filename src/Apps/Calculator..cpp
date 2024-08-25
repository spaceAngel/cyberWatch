#include "config.h"
#include "Calculator.h"

#include <LilyGoWatch.h>
#include "Core/Hardware/MotorController.h"
#include <string>

using namespace std;

void Calculator::render() {
	if (this->shouldReRender()) {
		this->renderKeyboard();
	}
	if (
		this->shouldReRender()
		|| this->currentNumber != this->prevDisplayedNumber
	) {
		this->renderDisplay();
	}
	this->setShouldReRender(false);
	this->prevDisplayedNumber = this->currentNumber;
}

void Calculator::renderKeyboard() {
	this->renderClearButton();
	this->renderButton(1, 1, "1", false);
	this->renderButton(2, 1, "2", false);
	this->renderButton(3, 1, "3", false);
	this->renderButton(1, 2, "4", false);
	this->renderButton(2, 2, "5", false);
	this->renderButton(3, 2, "6", false);
	this->renderButton(1, 3, "7", false);
	this->renderButton(2, 3, "8", false);
	this->renderButton(3, 3, "9", false);
	this->renderButton(1, 4, "0", false);
	this->renderButton(2, 4, ".", false);
	this->renderButton(4, 4, "/", true);
	this->renderButton(3, 4, "=", true);
	this->renderButton(4, 1, "+", true);
	this->renderButton(4, 2, "-", true);
	this->renderButton(4, 3, "*", true);
}

void Calculator::renderDisplay() {
	TTGOClass::getWatch()->tft->fillRoundRect(10, 10, 165, 40, 10, COLOR_BACKGROUND);
	TTGOClass::getWatch()->tft->drawRoundRect(10, 10, 165, 40, 10, COLOR_MAIN_1);

	uint8_t textStart = 158;
	if (this->currentNumber < 0) {
		textStart -= TTGOClass::getWatch()->tft->textWidth("-");
	}
	if (this->decimalCharCaret == 0) {
		if ((int) this->currentNumber == (float)this->currentNumber) {
			textStart -= (this->currentNumber == (float) 0 ? 1 : log10(abs(this->currentNumber))) * TTGOClass::getWatch()->tft->textWidth("1");
			TTGOClass::getWatch()->tft->drawNumber(this->currentNumber, textStart, 20);
		} else {
			textStart -= (this->currentNumber == (float) 0 ? 1 : log10(abs(this->currentNumber))) * TTGOClass::getWatch()->tft->textWidth("1");
			TTGOClass::getWatch()->tft->drawFloat(
				this->currentNumber,
				(int)(this->currentNumber * 100) % 10 == 0 ? 1 : 2,
				textStart - ((int)(this->currentNumber * 100) % 10 == 0 ? 1 : 2) * TTGOClass::getWatch()->tft->textWidth("0") - TTGOClass::getWatch()->tft->textWidth("."),
				20
			);
		}
	} else if (this->decimalCharCaret == 1) {
		char displayed[10];
		(void)snprintf(displayed, sizeof(displayed), "%d.", (int)this->currentNumber);
		textStart -= TTGOClass::getWatch()->tft->textWidth(displayed);
		TTGOClass::getWatch()->tft->drawString(displayed, textStart, 20);
	} else {
		textStart -= ((int)log10(this->currentNumber) + log10(this->decimalCharCaret) + 1) * TTGOClass::getWatch()->tft->textWidth("1");
		TTGOClass::getWatch()->tft->drawFloat(this->currentNumber, log10(this->decimalCharCaret), textStart, 20);
	}
}

void Calculator::renderClearButton() {
	TTGOClass::getWatch()->tft->fillRoundRect(182, 10, 48, 40, 10, COLOR_MAIN_3);
	TTGOClass::getWatch()->tft->drawString("C", 197, 18);
}

void Calculator::renderButton(
	uint8_t x,
	uint8_t y,
	char* symbol,
	bool background
) {
	uint8_t startY = 46;
	if (background) {
		TTGOClass::getWatch()->tft->fillRoundRect(
			(x - 1) * 57 + 10,
			(y - 1) * 45 + 10 + startY,
			50,
			40,
			10,
			COLOR_MAIN_3
		);
	} else {
		TTGOClass::getWatch()->tft->drawRoundRect(
			(x - 1) * 57 + 10,
			(y - 1) * 45 + 10 + startY,
			50,
			40,
			10,
			COLOR_MAIN_1
		);
	}
	TTGOClass::getWatch()->tft->drawString(
		symbol,
		(x - 1) * 57 + 28,
		(y - 1) * 45 + 20 + startY
	);

}

void Calculator::numberPressed(double number) {
	MotorController::vibrate(1);
	if (this->wasExecuted) {
		this->wasExecuted = false;
		this->currentNumber = 0;
		this->decimalCharCaret = 0;
	}
	if (this->decimalCharCaret == 0) {
		this->currentNumber *= 10;
		this->currentNumber += number;
	} else if (this->decimalCharCaret < 100) {
		this->decimalCharCaret *= 10;
		this->currentNumber += number / this->decimalCharCaret;
	}

}

void Calculator::clearPressed() {
	MotorController::vibrate(1);
	this->currentNumber = 0;
	this->decimalCharCaret = 0;
}

bool Calculator::handleTouch(uint8_t x, uint8_t y) {
	if (y < 40 && x > 197) {this->clearPressed();}
	if (y < 46) {
		return false;
	}
	uint8_t cellWidth = TFT_WIDTH / 4;
	uint8_t cellHeight = 45;
	uint8_t posX = (x/cellWidth) + 1;
	uint8_t posY = ((y - 50) /cellHeight) + 1;
	if (posX == 1 && posY == 1) {this->numberPressed(1);}
	if (posX == 2 && posY == 1) {this->numberPressed(2);}
	if (posX == 3 && posY == 1) {this->numberPressed(3);}
	if (posX == 1 && posY == 2) {this->numberPressed(4);}
	if (posX == 2 && posY == 2) {this->numberPressed(5);}
	if (posX == 3 && posY == 2) {this->numberPressed(6);}
	if (posX == 1 && posY == 3) {this->numberPressed(7);}
	if (posX == 2 && posY == 3) {this->numberPressed(8);}
	if (posX == 3 && posY == 3) {this->numberPressed(9);}
	if (posX == 1 && posY == 4) {this->numberPressed(0);}
	if (posX == 2 && posY == 4 && this->decimalCharCaret == 0) {
		MotorController::vibrate(1);
		this->decimalCharCaret = 1;
		this->prevDisplayedNumber = this->currentNumber == 0 ? 99 : 0;
	}
	if (posX == 4 && posY == 1) {this->operandPressed(OPERAND_PLUS);}
	if (posX == 4 && posY == 2) {this->operandPressed(OPERAND_MINUS);}
	if (posX == 4 && posY == 3) {this->operandPressed(OPERAND_MULTIPLE);}
	if (posX == 4 && posY == 4) {this->operandPressed(OPERAND_DIVIDE);}
	if (posX == 3 && posY == 4) {
		MotorController::vibrate(1);
		this->executePressed();
	}
	return false;
}

void Calculator::operandPressed(uint8_t operand) {
	MotorController::vibrate(1);
	if (
		this->prevNumber != NULL
		&& this->operand != NULL
	) {
		this->executePressed();
	}
	this->operand = operand;
	this->prevNumber = this->currentNumber;
	this->currentNumber = 0;
	this->decimalCharCaret = 0;

}

void Calculator::executePressed() {
	if (this->operand == OPERAND_PLUS) {this->currentNumber = this->prevNumber + this->currentNumber;}
	if (this->operand == OPERAND_MINUS) {this->currentNumber = this->prevNumber - this->currentNumber;}
	if (this->operand == OPERAND_DIVIDE) {this->currentNumber = this->prevNumber / this->currentNumber;}
	if (this->operand == OPERAND_MULTIPLE) {this->currentNumber = this->prevNumber * this->currentNumber;}
	this->decimalCharCaret = 0;
	this->prevNumber = NULL;
	this->operand = NULL;
	this->wasExecuted = true;
}