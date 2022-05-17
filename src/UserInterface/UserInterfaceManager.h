#pragma once

class UserInterfaceManager {

	public:

		static UserInterfaceManager *getInstance();

		void showSplashScreen();

		void showExitScreen();

		void render();

		bool handleTouch();

		protected:

			const uint8_t VECTOR_LEFT = 1;
			const uint8_t VECTOR_RIGHT = 2;
			const uint8_t VECTOR_UP = 1;
			const uint8_t VECTOR_DOWN = 2;

			uint16_t _swipeLastX = 0;
			uint8_t _swipeCounterHorizontal = 0;
			int8_t _swipeVectorHorizontal = 0;

			uint16_t _swipeLastY = 0;
			uint8_t _swipeCounterVertical = 0;
			int8_t _swipeVectorVertical = 0;

			bool _swipeEnabled = false;

			static UserInterfaceManager *_inst;


			UserInterfaceManager() {
			}

			void _stopSwipeHandlerHorizontal();

			void _handleSwipeHorizontal(uint x);

			void _stopSwipeHandlerVertical();

			void _handleSwipeVertical(uint y);

};
