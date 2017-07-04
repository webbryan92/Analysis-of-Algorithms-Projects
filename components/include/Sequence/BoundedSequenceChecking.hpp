#pragma once

//
// checking Version for BoundedSequence
// author: Dr. Holly
//


template <
	template <class, int> class BoundedSequence,
	class T,
	int maxLength
>
class BoundedSequenceChecking1 :
	public BoundedSequence <T, maxLength>
{
	typedef BoundedSequence <T, maxLength> SequenceOfT;
public:

	//-----------------------------------------------------------------------

	void add(
		preserves Integer pos,
		alters T& x
		)
	{
		// assert that |self| + 1 <= maxLength
		if (SequenceOfT::length() + 1 > maxLength) {
			OutputDebugString("Operation: add\n");
			OutputDebugString("Assertion failed: |self| + 1 <= maxLength\n");
			DebugBreak();
		}	// end if 
		// assert that 0 <= pos <= s.length
		if (pos < 0) {
			OutputDebugString("Operation: add\n");
			OutputDebugString("Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (pos > SequenceOfT::length()) {
			OutputDebugString("Operation: add\n");
			OutputDebugString("Assertion failed: pos <= |s|\n");
			DebugBreak();
		}	// end if 

		SequenceOfT::add(pos, x);
	}	// add

	//-----------------------------------------------------------------------

	void remove(
		preserves Integer pos,
		alters T& x
		)
	{
		// assert that 0 <= pos < s.length
		if (pos < 0) {
			OutputDebugString("Operation: remove\n");
			OutputDebugString("Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (SequenceOfT::length() <= pos) {
			OutputDebugString("Operation: remove\n");
			OutputDebugString("Assertion failed: pos < |s|\n");
			DebugBreak();
		}	// end if 

		SequenceOfT::remove(pos, x);
	}	// remove

	//-----------------------------------------------------------------------

	void replaceEntry(
		preserves Integer pos,
		alters T& x
		)
	{
		// assert that 0 <= pos < s.length
		if (pos < 0) {
			OutputDebugString("Operation: replaceEntry\n");
			OutputDebugString("Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (SequenceOfT::length() <= pos) {
			OutputDebugString("Operation: replaceEntry\n");
			OutputDebugString("Assertion failed: pos < |s|\n");
			DebugBreak();
		}	// end if 

		SequenceOfT::replaceEntry(pos, x);
	}	// swapItem

	//-----------------------------------------------------------------------

	void split(
		preserves Integer pos,
		produces BoundedSequenceChecking1& otherS
		)
	{
		// assert that 0 <= pos <= s.length
		if (pos < 0) {
			OutputDebugString("Operation: split\n");
			OutputDebugString("Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (pos > SequenceOfT::length()) {
			OutputDebugString("Operation: split\n");
			OutputDebugString("Assertion failed: pos <= |s|\n");
			DebugBreak();
		}	// end if 

		SequenceOfT::split(pos, otherS);
	}	// split

	//-----------------------------------------------------------------------

	T& entry(
		preserves Integer pos
		)
	{
		// assert that 0 <= pos < s.length
		if (pos < 0) {
			OutputDebugString("Operation: entry\n");
			OutputDebugString("Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (SequenceOfT::length() <= pos) {
			OutputDebugString("Operation: entry\n");
			OutputDebugString("Assertion failed: pos < |s|\n");
			DebugBreak();
		}	// end if 

		return (SequenceOfT::entry(pos));
	}	// entry

		//-----------------------------------------------------------------------

	void append(BoundedSequenceChecking1& sToAppend)
	{
		// assert that |self| + |sToAppend| <= maxLength
		if ((SequenceOfT::length() + sToAppend.length()) > maxLength) {
			OutputDebugString("Operation: append\n");
			OutputDebugString("Assertion failed: |self| + |sToAppend| <= maxLength\n");
			DebugBreak();
		}	// end if 
		SequenceOfT::append(sToAppend);
	}	// append

};

