#include "config.h"

#include <LilyGoWatch.h>

#include "RunAfterCompilation.h"
#include "Environment/SystemInfo.h"

#include "timestamp.h"
#include "BuildDateTime.h"
#include "Core/Registry.h"

bool RunAfterCompilation::handle() {
	RunAfterCompilation *handler = new RunAfterCompilation();
	if (handler->isFirstRun()) {
		handler->afterFirstRunOperations();
		SystemInfo::getInstance()->setPlugState(true);
		return true;
	}
	return false;
}

bool RunAfterCompilation::isFirstRun() {
	if (
		 Registry::getInstance()->getValue(REGISTRY_BUILD_TIMESTAMP, 0) == compilationTimestamp
	) {
		return false;
	} else {
		this->markFirstRunIsOver();
		return true;
	}
}

void RunAfterCompilation::afterFirstRunOperations() {
	//set date & time
	TTGOClass::getWatch()->rtc->setDateTime(BUILD_YEAR, BUILD_MONTH, BUILD_DAY, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
}

void RunAfterCompilation::markFirstRunIsOver() {
	Registry::getInstance()->setValue(REGISTRY_BUILD_TIMESTAMP, compilationTimestamp);
}
