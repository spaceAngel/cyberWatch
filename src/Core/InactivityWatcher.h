#pragma once

#include "config.h"

class InactivityWatcher {

	public:

		static InactivityWatcher *getInstance();

		bool isInactive();
		void markActivity();

		bool isDetectedOnHand();

	protected:

		static InactivityWatcher *inst;

		const long INACTIVITY_TRESHOLD = 5;

		long lastActivity;

		long lastOnHandActivity;

		InactivityWatcher();
};
