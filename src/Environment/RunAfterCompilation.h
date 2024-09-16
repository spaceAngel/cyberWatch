#pragma once

class RunAfterCompilation {

	public:

		static bool handle();

		const char *buildTimestampFile = "/build.lock";

	protected:

		RunAfterCompilation() {
		}

		bool isFirstRun();

		void afterFirstRunOperations();

		void markFirstRunIsOver();
		void configureRTCviaBuildTime();

};
