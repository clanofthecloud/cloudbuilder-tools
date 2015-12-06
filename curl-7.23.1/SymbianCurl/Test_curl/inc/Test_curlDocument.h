/*
 ============================================================================
 Name		: Test_curlDocument.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __TEST_CURLDOCUMENT_h__
#define __TEST_CURLDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CTest_curlAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CTest_curlDocument application class.
 * An instance of class CTest_curlDocument is the Document part of the
 * AVKON application framework for the Test_curl example application.
 */
class CTest_curlDocument : public CAknDocument
	{
public:
	// Constructors and destructor

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Construct a CTest_curlDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CTest_curlDocument.
	 */
	static CTest_curlDocument* NewL(CEikApplication& aApp);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Construct a CTest_curlDocument for the AVKON application aApp
	 * using two phase construction, and return a pointer
	 * to the created object.
	 * @param aApp Application creating this document.
	 * @return A pointer to the created instance of CTest_curlDocument.
	 */
	static CTest_curlDocument* NewLC(CEikApplication& aApp);

	/**
	 * ~CTest_curlDocument
	 * Virtual Destructor.
	 */
	virtual ~CTest_curlDocument();

public:
	// Functions from base classes

	/**
	 * CreateAppUiL
	 * From CEikDocument, CreateAppUiL.
	 * Create a CTest_curlAppUi object and return a pointer to it.
	 * The object returned is owned by the Uikon framework.
	 * @return Pointer to created instance of AppUi.
	 */
	CEikAppUi* CreateAppUiL();

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CTest_curlDocument.
	 * C++ default constructor.
	 * @param aApp Application creating this document.
	 */
	CTest_curlDocument(CEikApplication& aApp);

	};

#endif // __TEST_CURLDOCUMENT_h__
// End of File
