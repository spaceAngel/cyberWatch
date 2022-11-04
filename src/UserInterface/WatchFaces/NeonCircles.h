#pragma once

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/WatchFaces/Components/NeonCircle.h"

class NeonCircles : public MainComponent {

	public:

		NeonCircles();
		void render();
		void setShouldReRender(bool shouldReRender);

	protected:

		NeonCircle *circles [2];

};
