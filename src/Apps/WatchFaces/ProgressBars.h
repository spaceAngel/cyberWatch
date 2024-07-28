#pragma once

#include "Apps/WatchFaces/WatchFace.h"
#include "Apps/WatchFaces/Components/ProgressBar.h"

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
