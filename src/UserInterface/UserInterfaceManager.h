#pragma once

class UserInterfaceManager {

	public:

		static UserInterfaceManager *getInstance();

		void showSplashScreen();

		void showExitScreen();

		void render();

		protected:

			static UserInterfaceManager *_inst;


			UserInterfaceManager() {
			}

};
