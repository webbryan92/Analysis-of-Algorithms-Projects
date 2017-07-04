#pragma once

//
// ceramicArray Checking Version
// author: Dr. Holly
//

template <
	template <class> class CeramicArray,
	class T
>
class CeramicArrayChecking1:
	public CeramicArray <T>
{
	typedef CeramicArray <T> ArrayOfT;
public:

//-----------------------------------------------------------------------

T& operator [] (preserves Integer index)
{
	Integer lowerBound;
	Integer upperBound;

	ArrayOfT::getBounds (lowerBound, upperBound);
	// assert that index is in bounds
	if ((index < lowerBound) || (upperBound < index)) {
		OutputDebugString ("Operation: operator []\n");
		OutputDebugString ("Assertion failed: (lowerBound <= index) && (index <= upperBound)\n");
		DebugBreak ();
	}	// end if 
	
	return (ArrayOfT::operator [] (index));
}	// operator []

//-----------------------------------------------------------------------

void setBounds (
	preserves Integer lower,
	preserves Integer upper
)
{
	if (lower > upper) {
		OutputDebugString ("Operation: operator []\n");
		OutputDebugString ("Assertion failed: (lower <= upper)\n");
		DebugBreak ();
	}	// end if 
	
	ArrayOfT::setBounds (lower, upper);
}	// setBounds

};

