#include "config.h"

#include <SPIFFS.h>
#include <FS.h>
#include <string.h>
#include <LilyGoWatch.h>

#include "RunAfterCompilation.h"

#include "timestamp.h"

void RunAfterCompilation::handle() {
	RunAfterCompilation *handler = new RunAfterCompilation();
	if (handler->isFirstRun()) {
		handler->afterFirstRunOperations();
	}
}

bool RunAfterCompilation::isFirstRun() {
	if (
		!SPIFFS.exists(this->buildTimestampFile)
	) {
		this->markFirstRunIsOver();
		return true;
	} else {
		fs::File file = SPIFFS.open(this->buildTimestampFile, FILE_READ);
		String fromFile = file.readString();
		file.close();
		if (fromFile == compilationTimestampStr) {
			return false;
		}
	}
	this->markFirstRunIsOver();
	return true;
}

void RunAfterCompilation::afterFirstRunOperations() {
	//set date & time
	#include "BuildDateTime.h"
	TTGOClass::getWatch()->rtc->setDateTime(BUILD_YEAR, BUILD_MONTH, BUILD_DAY, BUILD_HOUR, BUILD_MIN, BUILD_SEC);
}

void RunAfterCompilation::markFirstRunIsOver() {
	fs::File file = SPIFFS.open(this->buildTimestampFile, FILE_WRITE);
	file.print(compilationTimestampChar);
	file.close();
}
