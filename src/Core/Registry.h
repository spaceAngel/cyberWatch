#pragma once

#include <Preferences.h>

#define REGISTRY_WATCHFACE "watchface"
#define REGISTRY_DISPLAY_ADJUST "adjust"
#define REGISTRY_SETTINGS "settinngs"
#define REGISTRY_BUILD_TIMESTAMP "timestamp"
#define REGISTRY_ALARM "alarm"

class Registry {

	public:

		static const uint NAME_WATCH_FACE = 0;
		static const uint NAME_SETTINGS = 1;
		static const uint NAME_DISPLAY_ADJUST = 2;

		static Registry *getInstance();

		uint getValue(const char* key, uint defaultValue);

		void setValue(const char* key, uint value);

		void setValue(const char* key, const void* value, uint8_t size);
		size_t getBytes(const char* key, void * buf, size_t maxLen);



	protected:

		static const uint8_t REGISTRY_SIZE = 3;

		static Registry *inst;

		Preferences preferences;

		Registry();
};
