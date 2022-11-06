#pragma once

#include "UserInterface/Components/Component.h"

class WatchFace : public Component {
	public:

		void render();

		virtual bool hasToolbar() {
			return false;
		}

		virtual bool hasInfoPanel() {
			return false;
		}

};
