#pragma once

#include "UserInterface/WatchFaces/WatchFace.h"
#include "UserInterface/WatchFaces/Components/NeonCircle.h"

class NeonCircles : public WatchFace {

	public:

		NeonCircles();
		void render();
		void setShouldReRender(bool shouldReRender);

	protected:

		NeonCircle *circles [2];

};
