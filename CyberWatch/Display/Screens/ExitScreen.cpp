#pragma once

#include "Components/Logo.cpp"

class ExitScreen {

	public:

		void show() {

			TTGOClass::getWatch()->tft->fillRect(
				0,
				0,
				TTGOClass::getWatch()->tft->width(),
				TTGOClass::getWatch()->tft->height(),
				TFT_BLACK
			);

			Logo *logo = new Logo();
			logo->render();

			char message[20] = "leaving	 matrix";
			TTGOClass::getWatch()->tft->drawString(
				message,
				(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(message)) / 2,
				TTGOClass::getWatch()->tft->height() - 60
			);
		}

		 
};
