/*
 ============================================================================
 Name		: Test_curlAppUi.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __TEST_CURLAPPUI_h__
#define __TEST_CURLAPPUI_h__

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CTest_curlAppView;

// CLASS DECLARATION
/**
 * CTest_curlAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CTest_curlAppUi : public CAknAppUi
	{
public:
	// Constructors and destructor

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 */
	void ConstructL();

	/**
	 * CTest_curlAppUi.
	 * C++ default constructor. This needs to be public due to
	 * the way the framework constructs the AppUi
	 */
	CTest_curlAppUi();

	/**
	 * ~CTest_curlAppUi.
	 * Virtual Destructor.
	 */
	virtual ~CTest_curlAppUi();

private:
	// Functions from base classes

	/**
	 * From CEikAppUi, HandleCommandL.
	 * Takes care of command handling.
	 * @param aCommand Command to be handled.
	 */
	void HandleCommandL(TInt aCommand);

	/**
	 *  HandleStatusPaneSizeChange.
	 *  Called by the framework when the application status pane
	 *  size is changed.
	 */
	void HandleStatusPaneSizeChange();

	/**
	 *  From CCoeAppUi, HelpContextL.
	 *  Provides help context for the application.
	 *  size is changed.
	 */
	CArrayFix<TCoeHelpContext>* HelpContextL() const;

private:
	// Data

	/**
	 * The application view
	 * Owned by CTest_curlAppUi
	 */
	CTest_curlAppView* iAppView;

	};

#endif // __TEST_CURLAPPUI_h__
// End of File
