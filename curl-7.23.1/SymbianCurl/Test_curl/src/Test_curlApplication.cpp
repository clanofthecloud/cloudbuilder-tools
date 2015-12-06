/*
 ============================================================================
 Name		: Test_curlApplication.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "Test_curl.hrh"
#include "Test_curlDocument.h"
#include "Test_curlApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTest_curlApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CTest_curlApplication::CreateDocumentL()
	{
	// Create an Test_curl document, and return a pointer to it
	return CTest_curlDocument::NewL(*this);
	}

// -----------------------------------------------------------------------------
// CTest_curlApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CTest_curlApplication::AppDllUid() const
	{
	// Return the UID for the Test_curl application
	return KUidTest_curlApp;
	}

// End of File
