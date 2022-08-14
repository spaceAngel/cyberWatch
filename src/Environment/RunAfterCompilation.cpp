#include <SPIFFS.h>
#include <FS.h>
#include <string.h>

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
}

void RunAfterCompilation::markFirstRunIsOver() {
	fs::File file = SPIFFS.open(this->buildTimestampFile, FILE_WRITE);
	file.print(compilationTimestampChar);
	file.close();
}
