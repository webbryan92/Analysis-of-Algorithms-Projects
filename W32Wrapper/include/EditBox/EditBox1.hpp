#pragma once

// Window's Edit Box Widget
// Date: 08/2015
// Author: Dr. Holly


class EditBox1
{
	//! is modeled by tuple
	//!          attached: Boolean
	//!          hidden: Boolean
	//!          dimmed: Boolean
	//!          windowsIdNum: Integer
	//!   exemplar self
	//!   initialization
	//!      ensures:   self = (false, false, false, 0)

public:
	EditBox1 ();
	~EditBox1 ();
	void clear (void);
	void transferFrom (consumes EditBox1& source);

	void attach (
			preserves HWND parentWindow,
			preserves Integer windowsIdNum
		);
		//!   alters self
		//!   requires: !self.attached  and  windowsIdNum is a valid ID number of an 
		//!				edit box control that is a child of parentWindow
		//!    ensures: self.attached  and  self.windowsIdNum = windowsIdNum

	void getContents (produces Text& x);
		//!   preserves self
		//!   requires: self.attached
		//!    ensures:  a copy of the contents of edit box control are retrieved 
		//!				and stored in x

	void setContents (preserves Text& x);
		//!   preserves self
		//!   requires: self.attached
		//!    ensures:  a copy of x is stored in the contents of edit box control

	void hide (void);
		//!   alters self
		//!   requires: self.attached
		//!    ensures:  self.hidden  and  edit box control is hidden from view

	void unhide (void);
		//!   alters self
		//!   requires: self.attached
		//!    ensures:  !self.hidden  and  edit box control is not hidden from view

	void dim (void);
		//!   alters self
		//!   requires: self.attached
		//!    ensures:  self.dimmed  and  edit box control is dimmed

	void undim (void);
		//!   alters self
		//!   requires: self.attached
		//!    ensures:  !self.dimmed  and  edit box control is not dimmed

	Boolean isAttached (void);
		//!   preserves self
		//!    ensures:  isAttached = self.attached

	Boolean isHidden (void);
		//!   preserves self
		//!   requires: self.attached
		//!    ensures:  isHidden = self.hidden

	Boolean isDimmed (void);
		//!   preserves self
		//!   requires: self.attached
		//!    ensures:  isDimmed = self.dimmed

	Boolean isEvent (preserves WPARAM wParam);
		//!   preserves self
		//!   requires: self.attached
		//!    ensures:  isEvent = (self.windowsIdNum == LOWORD (wParam)) 

	Integer decodeEvent (preserves WPARAM wParam);
		//!   preserves self
		//!   requires: self.attached  and  isEvent (wParam)
		//!    ensures:  decodeEvent = HIWORD (wParam) 

	Integer windowsId (void);
		//!   preserves self
		//!   requires: self.attached
		//!    ensures:  windowsId = self.windowsIdNum 

	void setFocus (void);
		//!   preserves self
		//!   requires: self.attached
		//!    ensures:  edit box control receives input focus 
	
private: // Representation

	HWND window;
	Boolean attached;
	Boolean hidden;
	Boolean dimmed;
	Integer windowsIdNum;

	// Disallowed EditBox Operations
	EditBox1& operator = (const EditBox1& rhs);
	EditBox1 (const EditBox1& s);
	EditBox1* operator & (void) {return (this);};
	const EditBox1* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// Implementation of methods
//-----------------------------------------------------------------------

EditBox1::EditBox1 ()
{
	window = NULL;
}	// EditBox1

//-----------------------------------------------------------------------

EditBox1::~EditBox1 ()
{
}	// ~EditBox1

//-----------------------------------------------------------------------

void EditBox1::transferFrom (EditBox1 &source)
{
	window = source.window;
	source.window = NULL;

	attached.transferFrom(source.attached);
	hidden.transferFrom(source.hidden);
	dimmed.transferFrom(source.dimmed);
	windowsIdNum.transferFrom(source.windowsIdNum);
}	// transferFrom

//-----------------------------------------------------------------------

void EditBox1::clear (void)
{
	if (attached) {
		attached = false;
		dimmed = false;
		hidden = false;
		windowsIdNum = 0;
		window = NULL;
   }  // end if
}	// clear

//-----------------------------------------------------------------------

void EditBox1::attach (
			preserves HWND parentWindow,
			preserves Integer assignedWindowsIdNum
		)
{
	window = GetDlgItem (parentWindow, assignedWindowsIdNum);
	if (window != NULL) {
		windowsIdNum = assignedWindowsIdNum;
		attached = true;
	} // end if
}	// attach

//-----------------------------------------------------------------------

void EditBox1::getContents (Text& x)
{
	char* cString;
	Integer length;

	length = GetWindowTextLength (window) + 1;
	cString = new char [length];
	GetWindowText (window, ((LPSTR) cString), length);
	x = cString;
	delete [] cString;
}	// getContents

//-----------------------------------------------------------------------

void EditBox1::setContents (Text& x)
{
	SetWindowText (window, x);
}	// setContents

//-----------------------------------------------------------------------

void EditBox1::hide (void)
{
	ShowWindow (window, SW_HIDE);
	EnableWindow (window, false);
	hidden = true;
}	// hide

//-----------------------------------------------------------------------

void EditBox1::unhide (void)
{
	EnableWindow (window, true);
	ShowWindow (window, SW_SHOWNORMAL);
	hidden = false;
}	// unhide

//-----------------------------------------------------------------------
void EditBox1::dim (void)
{
	EnableWindow (window, false);
	dimmed = true;
}	// dim

//-----------------------------------------------------------------------

void EditBox1::undim (void)
{
	EnableWindow (window, true);
	dimmed = false;
}	// undim

//-----------------------------------------------------------------------

Boolean EditBox1::isAttached (void)
{
	return (attached);
}	// isAttached

//-----------------------------------------------------------------------

Boolean EditBox1::isHidden (void)
{
	return (hidden);
}	// isHidden

//-----------------------------------------------------------------------

Boolean EditBox1::isDimmed (void)
{
	return (dimmed);
}	// isDimmed

//-----------------------------------------------------------------------

Boolean EditBox1::isEvent (WPARAM wParam)
{
	return (windowsIdNum == LOWORD (wParam));
}	// isEvent

//-----------------------------------------------------------------------

Integer EditBox1::decodeEvent (WPARAM wParam)
{
	return (HIWORD (wParam));
}	// decodeEvent

//-----------------------------------------------------------------------

Integer EditBox1::windowsId (void)
{
	return (windowsIdNum);
}	// windowsId

//-----------------------------------------------------------------------

void EditBox1::setFocus (void)
{
	SetFocus (window);
}	// setFocus

