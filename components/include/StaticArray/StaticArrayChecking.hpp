#pragma once

//
// staticArray Checking Version
// author: Dr. Holly
//

template <
		template <class, int, int> class StaticArray,
		class T,
		int lowerBound,
		int upperBound
	>
class StaticArrayChecking1:
	public StaticArray <T, lowerBound, upperBound>
{
	typedef StaticArray <T, lowerBound, upperBound> ArrayOfT;
public:
T& operator [] (preserves Integer index)
{
	// assert that index is in bounds
	if ((index < lowerBound) || (upperBound < index)) {
		OutputDebugString ("Operation: operator []\n");
		OutputDebugString ("Assertion failed: (lowerBound <= index) && (index <= upperBound)\n");
		DebugBreak ();
	}	// end if 

	return (ArrayOfT::operator [] (index));
}	// operator []

};


