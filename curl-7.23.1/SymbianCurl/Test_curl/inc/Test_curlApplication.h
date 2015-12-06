/*
 ============================================================================
 Name		: Test_curlApplication.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __TEST_CURLAPPLICATION_H__
#define __TEST_CURLAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "Test_curl.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidTest_curlApp =
	{
	_UID3
	};

// CLASS DECLARATION

/**
 * CTest_curlApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CTest_curlApplication is the application part of the
 * AVKON application framework for the Test_curl example application.
 */
class CTest_curlApplication : public CAknApplication
	{
public:
	// Functions from base classes

	/**
	 * From CApaApplication, AppDllUid.
	 * @return Application's UID (KUidTest_curlApp).
	 */
	TUid AppDllUid() const;

protected:
	// Functions from base classes

	/**
	 * From CApaApplication, CreateDocumentL.
	 * Creates CTest_curlDocument document object. The returned
	 * pointer in not owned by the CTest_curlApplication object.
	 * @return A pointer to the created document object.
	 */
	CApaDocument* CreateDocumentL();
	};

#endif // __TEST_CURLAPPLICATION_H__
// End of File
