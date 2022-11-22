#pragma once

#include "config.h"

class InactivityWatcher {

	public:

		static InactivityWatcher *getInstance();

		bool isInactive();
		void markActivity();

		void checkAndMarkIfOnHand();

		bool isDetectedOnHand();

	protected:

		static InactivityWatcher *inst;

		long lastActivity;

		long lastOnHandActivity;

		bool prevOnHandState = true;

		InactivityWatcher();
};
