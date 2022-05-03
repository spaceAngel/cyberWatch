#pragma once

#include "InfoPanelComponents/Battery.cpp"

class InfoPanel {
  public:

    InfoPanel() {
      _battery = new Battery();
    }

    void render() {
      _battery->render();
    }

  protected:

    Battery *_battery;

};
