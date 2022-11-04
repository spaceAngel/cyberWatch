#pragma once

#include "UserInterface/Components/MainComponent.h"

#include "UserInterface/Components/Icons/Battery.h"

class Toolbar : public MainComponent {

	public:

		void render();

		Toolbar();

		void setShouldReRender(bool shouldReRender);

	protected:

		Battery *battery;

		void renderDesign();

};