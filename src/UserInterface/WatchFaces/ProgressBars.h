#pragma once

#include "UserInterface/WatchFaces/Components/ProgressBar.h"

class ProgressBars : public MainComponent {

	public:

		void render();
		void setShouldReRender(bool shouldReRender);

		ProgressBars();

	protected:

		ProgressBar *bars[3];

};
