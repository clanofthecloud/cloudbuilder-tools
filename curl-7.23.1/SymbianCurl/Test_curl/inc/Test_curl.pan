/*
 ============================================================================
 Name		: Test_curl.pan
 Author	  : 
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __TEST_CURL_PAN__
#define __TEST_CURL_PAN__

/** Test_curl application panic codes */
enum TTest_curlPanics
	{
	ETest_curlUi = 1
	// add further panics here
	};

inline void Panic(TTest_curlPanics aReason)
	{
	_LIT(applicationName, "Test_curl");
	User::Panic(applicationName, aReason);
	}

#endif // __TEST_CURL_PAN__
