#include "App.h"

#include "UserInterface/AppRunner.h"

bool App::handlePEKShort() {
	AppRunner::getInstance()->setToDefaultApp();
	return true;
}