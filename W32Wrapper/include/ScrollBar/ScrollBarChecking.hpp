#pragma once
/*
	Checking Version for ScrollBar
	Author: Dr. Holly
*/


template <class ScrollBarUnchecked>
class ScrollBarChecking1:
	public ScrollBarUnchecked
{
public:

void attach (
		preserves HWND parent_window,
		preserves Integer scrollBarType
	)
{
	Text operationName ("attach");

	assertDetached (operationName);
	if ((scrollBarType != ScrollBarUnchecked::vScrollBar) &&
		(scrollBarType != ScrollBarUnchecked::hScrollBar)) {
		OutputDebugString ("Operation: attach\n");
		OutputDebugString ("Assertion Failed:\n");
		OutputDebugString ("\tscrollBarType == vScrollBar  or\n");
		OutputDebugString ("\tscrollBarType == hScrollBar\n");
		DebugBreak ();
	}	// end if 
	ScrollBarUnchecked::attach (parent_window, scrollBarType);
}	// attach

//-------------------------------------------------------------------

void setRange (preserves Integer min, preserves Integer max)
{
	Text operationName ("setRange");

	assertAttached (operationName);
	if ((min < 0) || (max < min)) {
		OutputDebugString ("Operation: setRange\n");
		OutputDebugString ("Assertion failed: 0 <= min <= max\n");
		DebugBreak ();
	}	// end if 
	ScrollBarUnchecked::setRange (min, max);
}	// setRange

//-------------------------------------------------------------------

void setScrollPosition (preserves Integer position)
{
	Text operationName ("setScrollPosition");

	assertAttached (operationName);
	if ((position < ScrollBarUnchecked::scrollMin ()) ||
		(position > ScrollBarUnchecked::scrollMax ())) {
		OutputDebugString ("Operation: setScrollPosition\n");
		OutputDebugString ("Assertion failed: self.scroll_min <= position <= self.scroll_max\n");
		DebugBreak ();
	}	// end if 
	ScrollBarUnchecked::setScrollPosition (position);
}	// setScrollPosition

//-------------------------------------------------------------------

void setUnits (preserves Integer line, preserves Integer page)
{
	Text operationName ("setUnits");

	assertAttached (operationName);
	if ((line < 1) || (page < 0)) {
		OutputDebugString ("Operation: setUnits\n");
		OutputDebugString ("Assertion failed: 1 <= line  and  0 <= page\n");
		DebugBreak ();
	}	// end if 
	ScrollBarUnchecked::setUnits (line, page);
}	// setUnits

//-------------------------------------------------------------------

void setWindowHeight (preserves Integer height)
{
	Text operationName ("setWindowHeight");

	assertAttached (operationName);
	if (height < 0) {
		OutputDebugString ("Operation: setWindowHeight\n");
		OutputDebugString ("Assertion failed: height >= 0\n");
		DebugBreak ();
	}	// end if 
	ScrollBarUnchecked::setWindowHeight (height);
}	// setWindowHeight

//-------------------------------------------------------------------

void setLineHeight (preserves Integer height)
{
	Text operationName ("setLineHeight");

	assertAttached (operationName);
	if (height <= 0) {
		OutputDebugString ("Operation: setLineHeight\n");
		OutputDebugString ("Assertion failed: height > 0\n");
		DebugBreak ();
	}	// end if 
	ScrollBarUnchecked::setLineHeight (height);
}	// setLineHeight

//-------------------------------------------------------------------

Integer scrollType (void)
{
	Text operationName ("scrollType");

	assertAttached (operationName);
	return (ScrollBarUnchecked::scrollType ());
}	// scrollType

//-------------------------------------------------------------------

Integer scrollMin (void)
{
	Text operationName ("scrollMin");

	assertAttached (operationName);
	return (ScrollBarUnchecked::scrollMin ());
}	// scrollMin

//-------------------------------------------------------------------

Integer scrollMax (void)
{
	Text operationName ("scrollMax");

	assertAttached (operationName);
	return (ScrollBarUnchecked::scrollMax ());
}	// scrollMin

//-------------------------------------------------------------------

Integer scrollPosition (void)
{
	Text operationName ("scrollPosition");

	assertAttached (operationName);
	return (ScrollBarUnchecked::scrollPosition ());
}	// scrollMin

//-------------------------------------------------------------------

Integer linesPerLineScroll (void)
{
	Text operationName ("linesPerLineScroll");

	assertAttached (operationName);
	return (ScrollBarUnchecked::linesPerLineScroll ());
}	// linesPerLineScroll

//-------------------------------------------------------------------

Integer linesPerPageScroll (void)
{
	Text operationName ("linesPerPageScroll");

	assertAttached (operationName);
	return (ScrollBarUnchecked::linesPerPageScroll ());
}	// linesPerPageScroll

//-------------------------------------------------------------------

Integer lineHeight (void)
{
	Text operationName ("lineHeight");

	assertAttached (operationName);
	return (ScrollBarUnchecked::lineHeight ());
}	// lineHeight

//-------------------------------------------------------------------

Integer windowHeight (void)
{
	Text operationName ("windowHeight");

	assertAttached (operationName);
	return (ScrollBarUnchecked::windowHeight ());
}	// windowHeight

//-------------------------------------------------------------------

Boolean isScrollEvent (preserves WPARAM wParam)
{
	Text operationName ("isScrollEvent");

	assertAttached (operationName);
	return (ScrollBarUnchecked::isScrollEvent (wParam));
}	// isScrollEvent

//-------------------------------------------------------------------

void handleScrollEvent (preserves WPARAM wParam)
{
	Text operationName ("windowHeight");

	assertAttached (operationName);
	if (!ScrollBarUnchecked::isScrollEvent (wParam)) {
		OutputDebugString ("Operation: handleScrollEvent\n");
		OutputDebugString ("Assertion failed: isScrollEvent (wParam)\n");
		DebugBreak ();
	}	// end if 
	ScrollBarUnchecked::handleScrollEvent (wParam);
}	// handleScrollEvent

private:

inline void assertAttached (preserves Text& operationName)
{
	// Assert that ScrollBar is attached
	// If it's not Attached, then output error message 
	// and transfer control to debugger.
	if (!ScrollBarUnchecked::isAttached ()) {
		Text output_string ("Operation: ");

		output_string.append (operationName);
		OutputDebugString (output_string);
		OutputDebugString ("\n");
		OutputDebugString ("Assertion Failed: is attached\n");
		DebugBreak ();
	}	// end if 
}	// assertAttached

//-------------------------------------------------------------------

inline void assertDetached (preserves Text& operationName)
{
	// Assert that ScrollBar is not attached
	// If it is Attached, then output error message 
	// and transfer control to debugger.
	if (ScrollBarUnchecked::isAttached ()) {
		Text output_string ("Operation: ");

		output_string.append (operationName);
		OutputDebugString (output_string);
		OutputDebugString ("\n");
		OutputDebugString ("Assertion Failed: not attached\n");
		DebugBreak ();
	}	// end if 
}	// assertDetached

};
