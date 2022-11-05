#pragma once

#include "UserInterface/Components/MainComponent.h"

class WatchFace : public MainComponent {
	public:

		void render();

		virtual bool hasToolbar() {
			return false;
		}

		virtual bool hasInfoPanel() {
			return false;
		}

};
