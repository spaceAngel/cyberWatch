#pragma once

class StepCounter {

  public:

    StepCounter() {
      _renderIcon();
    }

    void render() {
      TTGOClass::getWatch()->bma->readInterrupt();

      uint stepCount = TTGOClass::getWatch()->bma->getCounter();

      if (stepCount != _prevStepCount) {
        _clearDisplay();
        char steps[8];
        snprintf(
          steps,
          sizeof(steps),
          "%d",
          stepCount
        );
        
        TTGOClass::getWatch()->tft->drawString(steps, POS_X + 46, POS_Y + 1);
        _prevStepCount = stepCount;
      }
    }

  protected:
    const uint POS_X = 20;
    const uint POS_Y = 170;

    uint _prevStepCount = 0;
    uint _iconRendered = false;

    void _clearDisplay() {
      TTGOClass::getWatch()->tft->fillRect(
          POS_X + 44,
          POS_Y,
          100,
          TTGOClass::getWatch()->tft->fontHeight(),
          TFT_BLACK
        );
    }

    void _renderIcon() {
      TTGOClass::getWatch()->tft->fillEllipse(POS_X + 24, POS_Y + 10, 14, 8, TFT_DARKGREEN);
      TTGOClass::getWatch()->tft->fillCircle(POS_X + 4, POS_Y + 10, 8, TFT_DARKGREEN);
      TTGOClass::getWatch()->tft->fillRect(POS_X + 6, POS_Y + 2, 2, 18, TFT_DARKGREEN);
      TTGOClass::getWatch()->tft->fillRect(POS_X + 10, POS_Y, 3, 16, TFT_BLACK);
    }
};
