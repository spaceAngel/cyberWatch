#pragma once

class Battery {

  public:

    void render() {
      int capacity = TTGOClass::getWatch()->power->getBattPercentage();
      if (
        capacity < _prevCapacity //avoid blinking cause percentage is oscilating e.g. 94 - 96
        || (
          capacity != _prevCapacity
          && TTGOClass::getWatch()->power->isChargeing()
        )
      ) {
        char battery[6];
        snprintf(battery, sizeof(battery), "%d%%", capacity);
        TTGOClass::getWatch()->tft->fillRect(POS_X, POS_Y, 109, 26, TFT_BLACK);
        TTGOClass::getWatch()->tft->drawString(battery, POS_X + 46, POS_Y + 3);
        _renderBatteryIcon(capacity);
        _prevCapacity = capacity;
      }

      if (TTGOClass::getWatch()->power->isChargeing() != _prevChargingState) {
        if (TTGOClass::getWatch()->power->isChargeing()) {
          _renderChargingIcon();
        } else {
          TTGOClass::getWatch()->tft->fillRect(123, 143, 34, 20, TFT_BLACK); 
        }
        _prevChargingState = TTGOClass::getWatch()->power->isChargeing();
      }
    }

    void renderer() {
    }

  protected:
    int _prevCapacity = 101;
    bool _prevChargingState = false;

    const uint POS_X = 15;
    const uint POS_Y = 140;

    void _renderBatteryIcon(int capacity) {
      uint y = POS_Y + 4;
      uint x = POS_X + 3;
      uint thick = 2;
      uint height = 18;
      uint width = 36;
      uint innerWidth = width - 6 - 2 * thick;

      TTGOClass::getWatch()->tft->fillRect(x, y, width, height, TFT_DARKGREEN); 
      TTGOClass::getWatch()->tft->fillRect(x + thick, y + thick, width - 2 * thick , height - 2 * thick, TFT_BLACK); // inner box
      TTGOClass::getWatch()->tft->fillRect(
        x + width - 1,
        y + 4,
        6,
        height  - 8,
        TFT_DARKGREEN
      );

      float percentageBarWidth = ((float)capacity / (float)100) * (float)innerWidth ;
      TTGOClass::getWatch()->tft->fillRect(
        x + thick + 3,
        y + thick + 2,
        (int) percentageBarWidth,
        height - 4 - thick * 2,
        TFT_DARKGREEN
      );
    }

    void _renderChargingIcon() {
      int posX = 140;
      int posY = POS_Y + 12;
      TTGOClass::getWatch()->tft->fillCircle(posX + 4, posY, 8, TFT_DARKGREEN); 
      TTGOClass::getWatch()->tft->fillRect(posX - 15, posY - 2, 11, 4, TFT_DARKGREEN); 
      TTGOClass::getWatch()->tft->fillRect(posX + 8, posY - 6, 4, 16, TFT_BLACK); 
      TTGOClass::getWatch()->tft->fillRect(posX + 7, posY - 5, 9, 2, TFT_DARKGREEN); 
      TTGOClass::getWatch()->tft->fillRect(posX + 7, posY + 3, 9, 2, TFT_DARKGREEN); 
    }
};
