/*
 ============================================================================
 Name		: Test_curl.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "Test_curlApplication.h"

LOCAL_C CApaApplication* NewApplication()
	{
	return new CTest_curlApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

