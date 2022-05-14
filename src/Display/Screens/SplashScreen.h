#pragma once

#include "Components/Logo.h"

class SplashScreen {

  public:

    void show();

  protected:

    void _resetToDefault();

    void _renderLoadingBar();

};
