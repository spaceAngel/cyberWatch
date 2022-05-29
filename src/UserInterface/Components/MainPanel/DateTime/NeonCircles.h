#pragma once

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/DateTime/SubComponents/NeonCircle.h"

class NeonCircles : public MainComponent {

	public:

		NeonCircles();
		void render();
		void setShouldReRender(bool shouldReRender);

	protected:

		NeonCircle *_circles [2];

};
