#pragma once

class InactivityWatcher {

	public:

		static InactivityWatcher *getInstance();

		bool isInactive();
		void markActivity();

	protected:

		static InactivityWatcher *inst;

		const long INACTIVITY_TRESHOLD = 5;

		long lastActivity;

		InactivityWatcher();

};
