#pragma once

#include "InfoPanelComponents/Battery.cpp"
#include "InfoPanelComponents/StepCounter.cpp"

class InfoPanel {
  public:

    InfoPanel() {
      _battery = new Battery();
      _stepCounter = new StepCounter();
    }

    void render() {
      _battery->render();
      _stepCounter->render();
    }

  protected:

    Battery *_battery;
    StepCounter *_stepCounter;

};
