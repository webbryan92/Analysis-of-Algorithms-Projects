#pragma once
/*
	Checking Version for Edit Box
	Author: Dr. Holly
*/

template <class EditBoxBase>
class EditBoxChecking1:
	public EditBoxBase
{
public:

void attach (
			preserves HWND parentWindow,
			preserves Integer windowsIdNum
		)
{
	Text operationName("attach");

	assertDetached(operationName);
	EditBoxBase::attach(parentWindow, windowsIdNum);
} // attach

//-------------------------------------------------------------------

void getContents (produces Text& x)
{
	Text operationName("getContents");

	assertAttached(operationName);
	EditBoxBase::getContents(x);
} // getContents

//-------------------------------------------------------------------

void setContents (preserves Text& x)
{
	Text operationName("setContents");

	assertAttached(operationName);
	EditBoxBase::setContents(x);
}	// setContents

//-------------------------------------------------------------------

void hide (void)
{
	Text operationName("hide");

	assertAttached(operationName);
	EditBoxBase::hide();
}	// hide

//-------------------------------------------------------------------

void unhide (void)
{
	Text operationName("unhide");

	assertAttached(operationName);
	EditBoxBase::unhide();
}	// unhide

//-------------------------------------------------------------------

void dim (void)
{
	Text operationName("dim");

	assertAttached(operationName);
	EditBoxBase::dim();
}	// dim

//-------------------------------------------------------------------

void undim (void)
{
	Text operationName("undim");

	assertAttached(operationName);
	EditBoxBase::undim();
}	// undim

//-------------------------------------------------------------------

Boolean isHidden (void)
{
	Text operationName("isHidden");

	assertAttached(operationName);
	return(EditBoxBase::isHidden());
}	// isHidden

//-------------------------------------------------------------------

Boolean isDimmed (void)
{
	Text operationName("isDimmed");

	assertAttached(operationName);
	return(EditBoxBase::isDimmed());
}	// isDimmed

//-------------------------------------------------------------------

Boolean isEvent (preserves WPARAM wParam)
{
	Text operationName("isEvent");

	assertAttached(operationName);
	return(EditBoxBase::isEvent(wParam));
}	// isEvent

//-------------------------------------------------------------------

Integer decodeEvent (preserves WPARAM wParam)
{
	Text operationName("decodeEvent");

	assertAttached(operationName);
	if(!EditBoxBase::isEvent(wParam)) {
		OutputDebugString("Operation: decodeEvent\n");
		OutputDebugString("Assertion Failed: edit_box.isEvent(wParam)\n");
		DebugBreak();
	} // end if
	return (EditBoxBase::decodeEvent(wParam));
}	// decodeEvent

//-------------------------------------------------------------------

Integer windowsId (void)
{
	Text operationName("windowsId");

	assertAttached(operationName);
	return(EditBoxBase::windowsId());
}	// windowsId

//-------------------------------------------------------------------

void setFocus (void)
{
	Text operationName("setFocus");

	assertAttached(operationName);
	EditBoxBase::setFocus();
}	// setFocus

private:
inline void assertAttached(preserves Text& operationName)
{
	// Assert that Edit_Box is attached
	// If it's not Attached, then output error message 
	// and transfer control to debugger.
	if(!EditBoxBase::isAttached()) {
		Text outputString("Operation: ");

		outputString.append(operationName);
		OutputDebugString(outputString);
		OutputDebugString("\n");
		OutputDebugString("Assertion Failed: edit_box.isAttached()\n");
		DebugBreak();
	}	// end if 
}	// assertAttached

//-------------------------------------------------------------------

inline void assertDetached(preserves Text& operationName)
{
	// Assert that Edit_Box is not attached
	// If it is Attached, then output error message 
	// and transfer control to debugger.
	if(EditBoxBase::isAttached()) {
		Text outputString("Operation: ");

		outputString.append(operationName);
		OutputDebugString(outputString);
		OutputDebugString("\n");
		OutputDebugString("Assertion Failed: !edit_box.isAttached()\n");
		DebugBreak();
	}	// end if 
}	// assertDetached
};

