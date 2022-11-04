#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/Components/MainComponent.h"
#include "UserInterface/WatchFaces/Components/Date.h"
#include "UserInterface/WatchFaces/Components/Time.h"

class DigitalClocks : public MainComponent {

	public:
		void render();
		void setShouldReRender(bool shouldReRender);
		DigitalClocks();

	protected:

		Date *date;
		Time *time;


};
