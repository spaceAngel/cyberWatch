#if __has_include("NTPconf.h")
	#include "config.h"
	#include "NTP.h"
	#include <WiFi.h>
	#include <NTPClient.h>
	#include <LilyGoWatch.h>

	#include "NTPconf.h"

	#include "Environment/BuildDateTime.h"

	bool NTP::syncTime() {
		const char* ntpServer = "pool.ntp.org";
		const long gmtOffset_sec = NTP_OFFSET;
		const int daylightOffset_sec = NTP_OFFSET_DAYLIGHT;
		WiFi.mode(WIFI_STA); //Optional
		WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
		uint i = 0;
		while (
			WiFi.status() != WL_CONNECTED
		) {
			if (i > 20) {
				break;
			}
			delay(500);
			i++;
		}
		if (
			i > 20
			|| WiFi.status() != WL_CONNECTED
		)  {
			return false;
		} else {
			WiFiUDP ntpUDP;
			NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);
			configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
			timeClient.forceUpdate();
			TTGOClass::getWatch()->rtc->setDateTime(BUILD_YEAR, BUILD_MONTH, BUILD_DAY, timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
			return true;
		}
	}
#endif