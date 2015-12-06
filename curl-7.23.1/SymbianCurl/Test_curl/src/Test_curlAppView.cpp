/*
 ============================================================================
 Name		: Test_curlAppView.cpp
 Author	  : 
 Copyright   : Your copyright notice
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "Test_curlAppView.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTest_curlAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTest_curlAppView* CTest_curlAppView::NewL(const TRect& aRect)
	{
	CTest_curlAppView* self = CTest_curlAppView::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CTest_curlAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTest_curlAppView* CTest_curlAppView::NewLC(const TRect& aRect)
	{
	CTest_curlAppView* self = new (ELeave) CTest_curlAppView;
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
	}

// -----------------------------------------------------------------------------
// CTest_curlAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTest_curlAppView::ConstructL(const TRect& aRect)
	{
	// Create a window for this application view
	CreateWindowL();

	// Set the windows size
	SetRect(aRect);

	// Activate the window, which makes it ready to be drawn
	ActivateL();

	void TestCurl(void);
	TestCurl();
	}

// -----------------------------------------------------------------------------
// CTest_curlAppView::CTest_curlAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTest_curlAppView::CTest_curlAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CTest_curlAppView::~CTest_curlAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CTest_curlAppView::~CTest_curlAppView()
	{
	// No implementation required
	}

// -----------------------------------------------------------------------------
// CTest_curlAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CTest_curlAppView::Draw(const TRect& /*aRect*/) const
	{
	// Get the standard graphics context
	CWindowGc& gc = SystemGc();

	// Gets the control's extent
	TRect drawRect(Rect());

	// Clears the screen
	gc.Clear(drawRect);

	}

// -----------------------------------------------------------------------------
// CTest_curlAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CTest_curlAppView::SizeChanged()
	{
	DrawNow();
	}

// -----------------------------------------------------------------------------
// CTest_curlAppView::HandlePointerEventL()
// Called by framework to handle pointer touch events.
// Note: although this method is compatible with earlier SDKs, 
// it will not be called in SDKs without Touch support.
// -----------------------------------------------------------------------------
//
void CTest_curlAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{

	// Call base class HandlePointerEventL()
	CCoeControl::HandlePointerEventL(aPointerEvent);
	}

// End of File
