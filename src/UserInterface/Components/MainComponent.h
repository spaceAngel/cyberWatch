#pragma once

class MainComponent {

	public:

		void setShouldReRender(bool shouldReRender);

		bool shouldReRender();

		virtual void render() {};

	private:

		bool _shouldReRender = true;

};
