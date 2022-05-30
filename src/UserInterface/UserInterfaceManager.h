#pragma once

class UserInterfaceManager {

	public:

		static UserInterfaceManager *getInstance();

		void showSplashScreen();

		void showExitScreen();

		void render();

		bool handleTouch();

		void handlePEKShort();

		bool isSleepForbidden();

		protected:

			const int8_t VECTOR_LEFT = 1;
			const int8_t VECTOR_RIGHT = 2;
			const int8_t VECTOR_UP = 1;
			const int8_t VECTOR_DOWN = 2;

			uint16_t swipeLastX = 0;
			uint8_t swipeCounterHorizontal = 0;
			int8_t swipeVectorHorizontal = 0;

			uint16_t swipeLastY = 0;
			uint8_t swipeCounterVertical = 0;
			int8_t swipeVectorVertical = 0;

			bool swipeEnabled = false;

			static UserInterfaceManager *inst;


			UserInterfaceManager() {
			}

			void stopSwipeHandlerHorizontal();

			void handleSwipeHorizontal(uint x);

			void stopSwipeHandlerVertical();

			void handleSwipeVertical(uint y);

};
