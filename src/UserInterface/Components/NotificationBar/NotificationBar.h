#pragma once

#include "UserInterface/Components/MainComponent.h"

#include "UserInterface/Components/Icons/Battery.h"
#include "UserInterface/Components/NotificationBar/DeviceStatusIconBar.h"

class NotificationBar : public MainComponent {

	public:

		void render();

		NotificationBar();

		void setShouldReRender(bool shouldReRender);

	protected:

		Battery *battery;
		DeviceStatusIconBar *deviceStatusIconBar;

		void renderDesign();

};