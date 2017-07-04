// Simple File
// Date: 7/00
// Author: Dr. Holly

#include "wrapper.h"

//-----------------------------------------------------------------------
//	Local Operations
//-----------------------------------------------------------------------

void FileBase::getFileLength (void)
{
	static Integer zeroOffset = 0;
	static Integer fromEndOfFile = 2;
	static Integer fromBeginningOfFile = 0;

	fseek (rep->file, zeroOffset, fromEndOfFile);
	rep->fileLength = ftell (rep->file);
	fseek (rep->file, zeroOffset, fromBeginningOfFile);
}	// getFileLength

//-----------------------------------------------------------------------
//	Exported Operations
//-----------------------------------------------------------------------

FileBase::FileBase ()
{
   rep = new fileRep;
   rep->file = NULL;
}	// FileBase

//-----------------------------------------------------------------------

FileBase::~FileBase ()
{
	if (rep->fileOpen) {
		fclose (rep->file);
	}  // end if
	delete rep;
}	// ~FileBase

//-----------------------------------------------------------------------

void FileBase::transferFrom(FileBase& source)
{		rep->file = source.rep->file;
		source.rep->file = NULL;

		rep->fileOpen.transferFrom(source.rep->fileOpen);
		rep->fileLength.transferFrom(source.rep->fileLength);
		rep->ioDirection.transferFrom(source.rep->ioDirection);
} // transferFrom

//-----------------------------------------------------------------------

void FileBase::clear (void)
{
	if (rep->fileOpen) {
		fclose (rep->file);
	}  // end if
	delete rep;
	rep = new fileRep;
	rep->file = NULL;
}	// clear

//-----------------------------------------------------------------------

void FileBase::openFile (
			Text& fileName,
			Integer ioDirection,
			Boolean& successful
		)
{
	Integer readWrite, i, z;

	rep->ioDirection = ioDirection;
	switch (ioDirection) {
		case openForRead:
			WIN32_FIND_DATA findData;
			HANDLE fileHandle;

			// See if file exists, if not successful will be set to false
			fileHandle = FindFirstFile (fileName, &findData);
			successful = (fileHandle != INVALID_HANDLE_VALUE);
			if (successful) {
				FindClose (fileHandle);
				rep->file = fopen (fileName, "r");
				successful = (rep->file != NULL);
				getFileLength ();
			}	// end if
			break;
		case openForWrite:
			rep->file = fopen (fileName, "w");
			successful = (rep->file != NULL);
			break;
	}	// end switch

	if (successful)
		rep->fileOpen = true;
}	// openFile

//-----------------------------------------------------------------------

void FileBase::closeFile (
			Boolean& successful
		)
{
	const int successfulClose = 0;
	Integer return_code;

	rep->fileOpen = false;
	return_code = fclose (rep->file);
	successful = (return_code == successfulClose);
}	// closeFile

//-----------------------------------------------------------------------

Boolean FileBase::fileOpened (void)
{
	return (rep->fileOpen);
}	// fileOpened

//-----------------------------------------------------------------------

Integer FileBase::ioDirection (void)
{
	return (rep->ioDirection);
}	// ioDirection

//-----------------------------------------------------------------------

Boolean FileBase::endOfFile (void)
{
	LongInteger location;

	location = ftell (rep->file);
	return (rep->fileLength == location);
}	// endOfFile

//-----------------------------------------------------------------------

void FileBase::read (
			Character& x,
			Boolean& successful
		)
{
	char char_array[2];
	LongInteger itemsRead;

	// read the string, then copy to Text
	itemsRead = fread (char_array, 1, 1, rep->file);
	successful = ((itemsRead == 1) && !ferror (rep->file));

	if (successful) {
		x = char_array[0];
	}	// end if
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Character x,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Text s;

	s.add (0, x);

	itemsWritten = fwrite (s, 1, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Float& x,
			Boolean& successful
		)
{
	char* cString;
	float value;
	Integer stringLength;
	Integer itemsRead;

	// read string length, then convert to Integer
	read (stringLength, successful);
	if (successful) {
		cString = (char *)new char[stringLength + 1];

		// read the string, then copy to Text
		itemsRead = fread (cString, stringLength, 1, rep->file);
		successful = ((itemsRead == 1) && !ferror (rep->file));

		if (successful) {
			cString[stringLength] = '\0';
			sscanf (cString, "%f", &value);
			x = value;
		}	// end if
		delete [] cString;
	}	// end if
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Float x,
			Boolean& successful
		)
{
	char cString[30];
	Integer length;
	Integer itemsWritten;

	length = sprintf (cString, "%#.10f", (float)x);
	write (length, successful);
	itemsWritten = fwrite (cString, length, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Integer& x,
			Boolean& successful
		)
{
	char cString[6 + 1];
	int value;
	static Integer integerLengthBytes = 6;
	Integer stringLength;
	Integer itemsRead;

	// read value as string, then convert to Integer
	itemsRead = fread (cString, integerLengthBytes, 1, rep->file);
	successful = ((itemsRead == 1) && !ferror (rep->file));
	cString[integerLengthBytes] = '\0';
	sscanf (cString, "%d", &value);
	x = value;
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Integer x,
			Boolean& successful
		)
{
	char cString[6 + 1];
	static Integer integerLengthBytes = 6;
	Integer length;
	Integer stringLength;
	Integer itemsWritten;

	length = sprintf (cString, "%6d", (int)x);
	itemsWritten = fwrite (cString, length, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			LongInteger& x,
			Boolean& successful
		)
{
	char cString[25 + 1];
	long value;
	static Integer integerLengthBytes = 25;
	Integer stringLength;
	Integer itemsRead;

	// read value as string, then convert to Integer
	itemsRead = fread (cString, integerLengthBytes, 1, rep->file);
	successful = ((itemsRead == 1) && !ferror (rep->file));
	cString[integerLengthBytes] = '\0';
	sscanf (cString, "%ld", &value);
	x = value;
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			LongInteger x,
			Boolean& successful
		)
{
	char cString[25 + 1];
	static Integer longIntegerLengthBytes = 25;
	Integer length;
	Integer stringLength;
	Integer itemsWritten;

	length = sprintf (cString, "%25ld", (long)x);
	itemsWritten = fwrite (cString, length, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Boolean& x,
			Boolean& successful
		)
{
	Integer i;

	read (i, successful);
	x = (i == 1);
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Boolean x,
			Boolean& successful
		)
{
	Integer i;

	if (x) {
		i = 1;
		write (i, successful);
	} else {
		i = 0;
		write (i, successful);
	} // end if
}	// write

//-----------------------------------------------------------------------

void FileBase::read (
			Text& s,
			Boolean& successful
		)
{
	char* cString;
	Integer stringLength;
	Integer itemsRead;

	// read string length, then convert to Integer
	read (stringLength, successful);
	if (successful) {
		cString = (char *)new char[stringLength + 1];

		// read the string, then copy to Text
		itemsRead = fread (cString, stringLength, 1, rep->file);
		successful = ((itemsRead == 1) && !ferror (rep->file));

		if (successful) {
			cString[stringLength] = '\0';
			s = cString;
		}	// end if
		delete [] cString;
	}	// end if
}	// read

//-----------------------------------------------------------------------

void FileBase::write (
			Text& s,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Integer stringLength;

	stringLength = s.size ();
	write (stringLength, successful);
	if (successful) {
		itemsWritten = fwrite (s, s.size (), 1, rep->file);
		successful = ((itemsWritten == 1) && !ferror (rep->file));
	}	// end if
}	// write

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Boolean x,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Text t ("true");
	Text f ("false");

	if (x) {
		itemsWritten = fwrite (t, t.size (), 1, rep->file);
	} else {
		itemsWritten = fwrite (f, f.size (), 1, rep->file);
	}	// end if
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Character x,
			Boolean& successful
		)
{
	Integer itemsWritten;
	Text s;

	s.add (0, x);

	itemsWritten = fwrite (s, 1, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Float x,
			Boolean& successful
		)
{
	char cString[30];
	Integer length;
	Integer itemsWritten;

	length = sprintf (cString, "%f", (float)x);
	itemsWritten = fwrite (cString, length, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Integer x,
			Boolean& successful
		)
{
	char cString[30];
	Integer length;
	Integer itemsWritten;

	length = sprintf (cString, "%d", (int)x);
	itemsWritten = fwrite (cString, length, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			LongInteger x,
			Boolean& successful
		)
{
	char cString[30];
	Integer length;
	Integer itemsWritten;

	length = sprintf (cString, "%ld", (long)x);
	itemsWritten = fwrite (cString, length, 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// writeRaw

//-----------------------------------------------------------------------

void FileBase::writeRaw (
			Text& s,
			Boolean& successful
		)
{
	Integer itemsWritten;

	itemsWritten = fwrite (s, s.size (), 1, rep->file);
	successful = ((itemsWritten == 1) && !ferror (rep->file));
}	// writeRaw

