#include "StopWatchRegistry.h"

StopWatchRegistry* StopWatchRegistry::inst;

StopWatchRegistry *StopWatchRegistry::getInstance() {
	if (StopWatchRegistry::inst == nullptr) {
		StopWatchRegistry::inst = new StopWatchRegistry();
	}
	return StopWatchRegistry::inst;
}