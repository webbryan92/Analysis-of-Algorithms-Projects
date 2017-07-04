#pragma once

// Simple File
// Date: 7/99
// Author: Dr. Holly

class FileBase
{
public: // Standard Operations
	FileBase ();
	~FileBase ();
	void clear (void);
	void transferFrom(FileBase& source);

/*
	tuple of
		fileOpened : Boolean
		ioDirection : Integer
		eof : Boolean

  exemplar
		f

	initially
		!f.fileOpened  and  f.ioDirection = read  and  f.eof
*/

	enum {
		// File_Io_Constants
		openForRead			= 0,
		openForWrite		= 1,
		total			= 2
	};

	// FileBase Specific Operations
	void openFile (
			preserves Text& fileName,
			preserves Integer ioDirection,
			produces Boolean& successful
		);
	//!  pre: !f.fileOpened  and
	//!		(f.ioDirection = read  or  f.ioDirection = write)
	//! post:
	//!		(f.fileOpened  and  successful
	//!		 or
	//!		!f.fileOpened  and  !successful) 
	//!		and  f.ioDirection = ioDirection
	//!		and  f.eof  iff at end of file

	void closeFile (
			produces Boolean& successful
		);
	//!  pre: f.fileOpened
	//! post:
	//!		f.fileOpened

	Boolean fileOpened (void);
	//! post:
	//!		fileOpened = f.fileOpened

	Integer ioDirection (void);
	//!  pre: f.fileOpened
	//! post:
	//!		ioDirection = f.ioDirection

	Boolean endOfFile (void);
	//!  pre: f.fileOpened
	//! post:
	//!		endOfFile = f.eof
	
	void read (
			produces Boolean& x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Boolean  where y is
	//!		next formatted item to be read from the file
	//! post:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (
			produces Character& x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Character  where y is
	//!		next formatted item to be read from the file
	//! post:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (
			produces Float& x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Float  where y is
	//!		next formatted item to be read from the file
	//! post:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (
			produces Integer& x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Integer  where y is
	//!		next formatted item to be read from the file
	//! post:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void read (
			produces LongInteger& x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : LongInteger  where y is
	//!		next formatted item to be read from the file
	//! post:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly


	void read (
			produces Text& s,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = read  and  !f.eof
	//!		and  there exists a  y : Text  where y is
	//!		next formatted item to be read from the file
	//! post:
	//!		y has been read from file
	//!		and  x = y
	//!		and  f.eof  iff at end of file
	//!		and  successful if y was read correctly

	void write (
			preserves Boolean x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a formatted Boolean
	//!		and  successful if x was written correctly

	void write (
			preserves Character x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a formatted Character
	//!		and  successful if x was written correctly

	void write (
			preserves Float x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a formatted Float
	//!		and  successful if x was written correctly

	void write (
			preserves Integer x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a formatted Integer
	//!		and  successful if x was written correctly

	void write (
			preserves LongInteger x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a formatted LongInteger
	//!		and  successful if x was written correctly

	void write (
			preserves Text& s,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a formatted Text
	//!		and  successful if x was written correctly


	void writeRaw (
			preserves Boolean x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a unformatted Boolean
	//!		and  successful if x was written correctly

	void writeRaw (
			preserves Character x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a unformatted Character
	//!		and  successful if x was written correctly

	void writeRaw (
			preserves Float x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a unformatted Float
	//!		and  successful if x was written correctly

	void writeRaw (
			preserves Integer x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a unformatted Integer
	//!		and  successful if x was written correctly

	void writeRaw (
			preserves LongInteger x,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a unformatted LongInteger
	//!		and  successful if x was written correctly

	void writeRaw (
			preserves Text& s,
			produces Boolean& successful
		);
	//!  pre: f.fileOpened  and  f.ioDirection = write
	//! post:
	//!		x has been written to file the file as a unformatted Text
	//!		and  successful if x was written correctly


private: // Local Operations
	void getFileLength (void);

private: // Representation
	class fileRep {
	public:
		FILE* file;
		Boolean fileOpen;
		LongInteger fileLength;
		Integer ioDirection;
	};
	fileRep* rep;

	// Disallowed FileBase Operations
	FileBase& operator = (const FileBase& rhs);
	FileBase (const FileBase& s);
	FileBase* operator & (void) {return (this);};
	const FileBase* operator & (void) const {return (this);};
};	// end FileBase


