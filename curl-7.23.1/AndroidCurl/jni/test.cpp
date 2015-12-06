#include "include/curl/curl.h"
#include <android/log.h>

void testJNI(void)
{
	CURL *curl;

	curl	= curl_easy_init();
	if(curl)
	{
		CURLcode curlres;

		curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
		curlres = curl_easy_perform(curl);
		__android_log_print(ANDROID_LOG_ERROR, "Native Code", "res = %d", curlres);
		curl_easy_cleanup(curl);
	}
}