#include "EventManager.h"

EventManager* EventManager::inst;

EventManager *EventManager::getInstance() {
	if (EventManager::inst == nullptr) {
		EventManager::inst = new EventManager();
	}
	return EventManager::inst;
}

void EventManager::fireEvent(uint8_t event) {
	for (uint8_t i = 0; i < this->listenersCount; i++) {
		if (this->listeners[i]->listen(event)) {
			this->listeners[i]->handle();
		}
	}
}
