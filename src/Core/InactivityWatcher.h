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

		long lastActivity;

		long lastOnHandActivity;

		InactivityWatcher();
};
