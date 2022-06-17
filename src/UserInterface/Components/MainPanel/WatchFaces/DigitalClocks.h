#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/Components/MainPanel/WatchFaces/SubComponents/Date.h"
#include "UserInterface/Components/MainPanel/WatchFaces/SubComponents/Time.h"

class DigitalClocks : public MainComponent {

	public:
		void render();
		void setShouldReRender(bool shouldReRender);
		DigitalClocks();

	protected:

		Date *date;
		Time *time;


};
