#pragma once

#include "UserInterface/WatchFaces/WatchFace.h"
#include "UserInterface/WatchFaces/Components/ProgressBar.h"

class ProgressBars : public WatchFace {

	public:

		void render();
		void setShouldReRender(bool shouldReRender);

		ProgressBars();

		bool hasInfoPanel() {
			return true;
		}

	protected:

		ProgressBar *bars[3];

};
