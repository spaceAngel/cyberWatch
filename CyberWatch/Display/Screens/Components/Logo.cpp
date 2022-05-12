#pragma once

class Logo {

	public:

		void render() {
			TTGOClass::getWatch()->tft->setTextFont(2);
			TTGOClass::getWatch()->tft->setTextSize(3);

			TTGOClass::getWatch()->tft->drawString(
				APP_NAME,
				(TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(APP_NAME)) / 2,
				TTGOClass::getWatch()->tft->height() / 2 - TTGOClass::getWatch()->tft->fontHeight()
			);

			TTGOClass::getWatch()->tft->setTextSize(2);
			TTGOClass::getWatch()->tft->drawString(
				APP_VERSION,
	      (TTGOClass::getWatch()->tft->width() - TTGOClass::getWatch()->tft->textWidth(APP_VERSION)) / 2,
        TTGOClass::getWatch()->tft->height() / 2
      );
    }

};
