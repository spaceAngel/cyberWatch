#pragma once

class RunAfterCompilation {

	public:

		static void handle();

		const char *buildTimestampFile = "/build.lock";

	protected:

		RunAfterCompilation() {
		}

		bool isFirstRun();

		void afterFirstRunOperations();

		void markFirstRunIsOver();

};
