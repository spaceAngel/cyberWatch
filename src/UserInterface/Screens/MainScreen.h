#pragma once

#include "UserInterface/App.h"
#include "UserInterface/Components/NotificationBar/NotificationBar.h"

class MainScreen {

	public:

		static MainScreen *getInstance();

		void render();

		void handleSwipeHorizontal(int vector);
		void handleSwipeVertical(int vector);
		void handlePEKShort();
		void handleTouch(uint8_t x, uint8_t y, bool isLongTouch);
		void switchApp(int vector);
		void destroy();
		void clear();
		NotificationBar *getNotificationBar();


	protected:

		static MainScreen *inst;

		NotificationBar *notificationBar;

		MainScreen();

};
