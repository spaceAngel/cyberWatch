#pragma once

#include "Apps/WatchFaces/WatchFace.h"
#include "Apps/WatchFaces/Components/NeonCircle.h"

class NeonCircles : public WatchFace {

	public:

		NeonCircles();
		void render();
		void setShouldReRender(bool shouldReRender);

		bool hasInfoPanel() {
			return true;
		}

	protected:

		NeonCircle *circles [2];

};
