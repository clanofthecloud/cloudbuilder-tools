/*
 ============================================================================
 Name		: Test_curlAppView.h
 Author	  : 
 Copyright   : Your copyright notice
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __TEST_CURLAPPVIEW_h__
#define __TEST_CURLAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>

// CLASS DECLARATION
class CTest_curlAppView : public CCoeControl
	{
public:
	// New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CTest_curlAppView object, which will draw itself to aRect.
	 * @param aRect The rectangle this view will be drawn to.
	 * @return a pointer to the created instance of CTest_curlAppView.
	 */
	static CTest_curlAppView* NewL(const TRect& aRect);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Create a CTest_curlAppView object, which will draw itself
	 * to aRect.
	 * @param aRect Rectangle this view will be drawn to.
	 * @return A pointer to the created instance of CTest_curlAppView.
	 */
	static CTest_curlAppView* NewLC(const TRect& aRect);

	/**
	 * ~CTest_curlAppView
	 * Virtual Destructor.
	 */
	virtual ~CTest_curlAppView();

public:
	// Functions from base classes

	/**
	 * From CCoeControl, Draw
	 * Draw this CTest_curlAppView to the screen.
	 * @param aRect the rectangle of this view that needs updating
	 */
	void Draw(const TRect& aRect) const;

	/**
	 * From CoeControl, SizeChanged.
	 * Called by framework when the view size is changed.
	 */
	virtual void SizeChanged();

	/**
	 * From CoeControl, HandlePointerEventL.
	 * Called by framework when a pointer touch event occurs.
	 * Note: although this method is compatible with earlier SDKs, 
	 * it will not be called in SDKs without Touch support.
	 * @param aPointerEvent the information about this event
	 */
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
	// Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 * Perform the second phase construction of a
	 * CTest_curlAppView object.
	 * @param aRect The rectangle this view will be drawn to.
	 */
	void ConstructL(const TRect& aRect);

	/**
	 * CTest_curlAppView.
	 * C++ default constructor.
	 */
	CTest_curlAppView();

	};

#endif // __TEST_CURLAPPVIEW_h__
// End of File
