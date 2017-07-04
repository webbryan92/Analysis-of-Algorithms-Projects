#pragma once
#include <commdlg.h>

// Common File Dialog - wrapper for Windows common file dialog box
// Date: 11/13
// Author: Dr. Holly

class CommonFileDialog
{
public: // Standard Operations
	CommonFileDialog ();
	~CommonFileDialog ();
	void clear (void);
	void transferFrom(CommonFileDialog& source);
	CommonFileDialog& operator = (CommonFileDialog& rhs);

	// CommonFileDialog Specific Operations
	void getOpenFilename (
			preserves HWND parent_window,
			produces Text& pathName,
			produces Text& fileName,
			produces Boolean& successful
		);

	void getSaveDataFilename (
			preserves HWND parent_window,
			produces Text& pathName,
			produces Text& fileName,
			produces Boolean& successful
		);


private: // Representation

	// Disallowed CommonFileDialog Operations
	CommonFileDialog (const CommonFileDialog& s);
	CommonFileDialog* operator & (void) {return (this);};
	const CommonFileDialog* operator & (void) const {return (this);};

};	// end CommonFileDialog


//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

CommonFileDialog::CommonFileDialog ()
{
}	// CommonFileDialog

//-----------------------------------------------------------------------

CommonFileDialog::~CommonFileDialog ()
{
}	// ~CommonFileDialog

//-----------------------------------------------------------------------

void CommonFileDialog::transferFrom(CommonFileDialog& source)
{
} // transferFrom

//-----------------------------------------------------------------------

CommonFileDialog&
CommonFileDialog::operator = (CommonFileDialog& rhs)
{
	return (*this);
} // operator =

//-----------------------------------------------------------------------

void CommonFileDialog::clear (void)
{
}	// clear

//-----------------------------------------------------------------------

void CommonFileDialog::getOpenFilename (
			HWND parent_window,
			Text& pathName,
			Text& fileName,
			Boolean& successful
		)
{
	static char szFilter[] = 
		"Data File (*.dat)\0*.dat\0" \
		"All Files (*.*)\0*.*\0\0";

	char fn[_MAX_PATH] = "*.dat";
	char file_title[_MAX_FNAME + _MAX_EXT];
	OPENFILENAME ofn;

	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	ofn.lStructSize       = sizeof (OPENFILENAME);
	ofn.hwndOwner         = parent_window;
	ofn.hInstance         = NULL;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter    = 0;
	ofn.nFilterIndex      = 0;
	ofn.lpstrFile         = fn;
	ofn.nMaxFile          = _MAX_PATH;
	ofn.lpstrFileTitle    = file_title;
	ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir   = NULL;
	ofn.lpstrTitle        = NULL;
	ofn.nFileOffset       = 0;
	ofn.nFileExtension    = 0;
	ofn.lpstrDefExt       = "dat";
	ofn.lCustData         = 0L;
	ofn.lpfnHook          = NULL;
	ofn.lpTemplateName    = NULL;

	successful = GetOpenFileName (&ofn);

	if (successful) {
		fileName = file_title;
		pathName = fn;
	}	// end if
}	// getOpenFilename

//-----------------------------------------------------------------------

void CommonFileDialog::getSaveDataFilename (
			HWND parent_window,
			Text& pathName,
			Text& fileName,
			Boolean& successful
		)
{
	static char szFilter[] = 
		"Data File (*.dat)\0*.dat\0" \
		"All Files (*.*)\0*.*\0\0";
	char fn[_MAX_PATH] = "*.dat";
	char file_title[_MAX_FNAME + _MAX_EXT];
	OPENFILENAME ofn;

	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;

	ofn.lStructSize       = sizeof (OPENFILENAME);
	ofn.hwndOwner         = parent_window;
	ofn.hInstance         = NULL;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter    = 0;
	ofn.nFilterIndex      = 0;
	ofn.lpstrFile         = fn;
	ofn.nMaxFile          = _MAX_PATH;
	ofn.lpstrFileTitle    = file_title;
	ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir   = NULL;
	ofn.lpstrTitle        = NULL;
	ofn.nFileOffset       = 0;
	ofn.nFileExtension    = 0;
	ofn.lpstrDefExt       = "dat";
	ofn.lCustData         = 0L;
	ofn.lpfnHook          = NULL;
	ofn.lpTemplateName    = NULL;

	successful = GetSaveFileName (&ofn);
	if (successful) {
		fileName = fn;
		pathName = file_title;
	}	// end if
}	// getSaveDataFilename

