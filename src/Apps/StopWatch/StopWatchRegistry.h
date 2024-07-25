#pragma once

#include "config.h"

#include <LilyGoWatch.h>

#include "UserInterface/App.h"

class StopWatchRegistry {
	public:

		static StopWatchRegistry *getInstance();

		bool getRunning() {
			return this->running;
		}

		void setRunning(bool running) {
			this->running = running;
		}

		int64_t getStartAt() {
			return this->startAt;
		}

		void setStartAt(int64_t startAt) {
			this->startAt = startAt;
		}

		int64_t getStopAt() {
			return this->stopAt;
		}

		void setStopAt(int64_t stopAt) {
			this->stopAt = stopAt;
		}



	protected:

		static StopWatchRegistry *inst;


		StopWatchRegistry() {}


		int64_t startAt = 0;
		int64_t stopAt = 0;

		bool running = false;

};
