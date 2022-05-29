#pragma once

#include "UserInterface/Components/MainPanel/DateTime/SubComponents/ProgressBar.h"

class ProgressBars : public MainComponent {

	public:

		void render();
		void setShouldReRender(bool shouldReRender);

		ProgressBars();

	protected:

		ProgressBar *_bars[3];

};
