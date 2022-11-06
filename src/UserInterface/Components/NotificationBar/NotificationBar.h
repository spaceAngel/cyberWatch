#pragma once

#include "UserInterface/Components/Component.h"

#include "UserInterface/Components/Icons/Battery.h"
#include "UserInterface/Components/NotificationBar/DeviceStatusIconBar.h"

class NotificationBar : public Component {

	public:

		void render();

		NotificationBar();

		void setShouldReRender(bool shouldReRender);

	protected:

		Battery *battery;
		DeviceStatusIconBar *deviceStatusIconBar;

		void renderDesign();

};