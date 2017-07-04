#pragma once

/*
	Checking Version of File
	Author: Dr. Holly
*/

template <class StandardFile>
class FileChecking1:
	public StandardFile
{
public:
	void openFile (
			preserves Text& fileName,
			preserves Integer ioDirection,
			produces Boolean& successful
		);
	void closeFile (
			produces Boolean& successful
		);

	Integer ioDirection (void);

	Boolean endOfFile (void);

	void read (
			produces Boolean& x,
			produces Boolean& successful
		);

	void read (
			produces Character& x,
			produces Boolean& successful
		);

	void read (
			produces Float& x,
			produces Boolean& successful
		);

	void read (
			produces LongInteger& x,
			produces Boolean& successful
		);

	void read (
			produces Integer& x,
			produces Boolean& successful
		);

	void read (
			produces Text& s,
			produces Boolean& successful
		);

	void write (
			preserves Boolean x,
			produces Boolean& successful
		);

	void write (
			preserves Character x,
			produces Boolean& successful
		);

	void write (
			preserves Float x,
			produces Boolean& successful
		);

	void write (
			preserves LongInteger x,
			produces Boolean& successful
		);

	void write (
			preserves Integer x,
			produces Boolean& successful
		);

	void write (
			preserves Text& s,
			produces Boolean& successful
		);

	void writeRaw (
			preserves Boolean x,
			produces Boolean& successful
		);

	void writeRaw (
			preserves Character x,
			produces Boolean& successful
		);

	void writeRaw (
			preserves Float x,
			produces Boolean& successful
		);

	void writeRaw (
			preserves LongInteger x,
			produces Boolean& successful
		);

	void writeRaw (
			preserves Integer x,
			produces Boolean& successful
		);

	void writeRaw (
			preserves Text& s,
			produces Boolean& successful
		);
};


//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------


template <class StandardFile>
void FileChecking1<StandardFile>::openFile (
			preserves Text& fileName,
			preserves Integer ioDirection,
			produces Boolean& successful
		)
{
	// Assert that file is not open
	if (StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: openFile\n");
		OutputDebugString ("Assertion failed: !fileOpened\n");
		DebugBreak ();
	}	// end if 

	// Assert that ioDirection is correct
	if (!(ioDirection == StandardFile::openForRead || ioDirection == StandardFile::openForWrite)) {
		OutputDebugString ("Operation: openFile\n");
		OutputDebugString ("Assertion failed: correct ioDirection\n");
		DebugBreak ();
	}	// end if

	StandardFile::openFile (fileName, ioDirection, successful);
}	// openFile

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::closeFile (
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: closeFile\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	StandardFile::closeFile (successful);
}	// closeFile

//-------------------------------------------------------------------

template <class StandardFile>
Integer FileChecking1<StandardFile>::ioDirection (void)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: ioDirection\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	return (StandardFile::ioDirection ());
}	// ioDirection

//-------------------------------------------------------------------

template <class StandardFile>
Boolean FileChecking1<StandardFile>::endOfFile (void)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: endOfFile\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	return (StandardFile::endOfFile ());
}	// endOfFile

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (
			produces Boolean& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (
			produces Character& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (
			produces Float& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (
			produces LongInteger& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (
			produces Integer& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::read (
			produces Text& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForRead) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: File Opened For read\n");
		DebugBreak ();
	}	// end if 
	// Assert not EOF
	if (StandardFile::endOfFile ()) {
		OutputDebugString ("Operation: read\n");
		OutputDebugString ("Assertion failed: Not EOF\n");
		DebugBreak ();
	}	// end if 

	StandardFile::read (x, successful);
}	// read

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (
			produces Boolean x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (
			produces Character x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (
			produces Float x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (
			produces LongInteger x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (
			produces Integer x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::write (
			produces Text& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: write\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::write (x, successful);
}	// write

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (
			produces Boolean x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (
			produces Character x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (
			produces Float x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (
			produces LongInteger x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (
			produces Integer x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

//-------------------------------------------------------------------

template <class StandardFile>
void FileChecking1<StandardFile>::writeRaw (
			produces Text& x,
			produces Boolean& successful
		)
{
	// Assert that file is open
	if (!StandardFile::fileOpened ()) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: fileOpened\n");
		DebugBreak ();
	}	// end if 
	// Assert opened for reading
	if (StandardFile::ioDirection () != StandardFile::openForWrite) {
		OutputDebugString ("Operation: writeRaw\n");
		OutputDebugString ("Assertion failed: File Opened For write\n");
		DebugBreak ();
	}	// end if 

	StandardFile::writeRaw (x, successful);
}	// writeRaw

