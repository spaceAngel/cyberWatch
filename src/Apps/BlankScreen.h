#pragma once

#include "UserInterface/App.h"

#include "config.h"

class BlankScreen : public App {

	public:
		void render();

		BlankScreen() {}

		virtual bool hasNotificationBar() {
			return false;
		}

	protected:

};
