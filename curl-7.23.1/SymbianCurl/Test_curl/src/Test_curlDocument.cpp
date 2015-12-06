/*
 ============================================================================
 Name		: Test_curlDocument.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : CTest_curlDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "Test_curlAppUi.h"
#include "Test_curlDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTest_curlDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTest_curlDocument* CTest_curlDocument::NewL(CEikApplication& aApp)
	{
	CTest_curlDocument* self = NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CTest_curlDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTest_curlDocument* CTest_curlDocument::NewLC(CEikApplication& aApp)
	{
	CTest_curlDocument* self = new (ELeave) CTest_curlDocument(aApp);

	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CTest_curlDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTest_curlDocument::ConstructL()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CTest_curlDocument::CTest_curlDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTest_curlDocument::CTest_curlDocument(CEikApplication& aApp) :
	CAknDocument(aApp)
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CTest_curlDocument::~CTest_curlDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CTest_curlDocument::~CTest_curlDocument()
	{
	// No implementation required
	}

// ---------------------------------------------------------------------------
// CTest_curlDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CTest_curlDocument::CreateAppUiL()
	{
	// Create the application user interface, and return a pointer to it;
	// the framework takes ownership of this object
	return new (ELeave) CTest_curlAppUi;
	}

// End of File
