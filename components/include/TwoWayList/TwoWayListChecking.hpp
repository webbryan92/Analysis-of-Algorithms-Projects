#pragma once

/*
	Checking Version of TwoWayList
	Author: Dr. Holly
*/

template <
	template <class> class TwoWayList,
	class T
>
class TwoWayListChecking1:
	public TwoWayList <T>
{
	typedef TwoWayList <T> ListOfT;
public:

//-------------------------------------------------------------------

void advance (void)
{
	// assert that right size > 0
	if (ListOfT::rightLength() <= 0) {
		OutputDebugString("Operation: advance\n");
		OutputDebugString("Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	ListOfT::advance();
}	// advance

//-------------------------------------------------------------------

void retreat (void)
{
	// assert that left size > 0
	if (ListOfT::leftLength() <= 0) {
		OutputDebugString("Operation: retreat\n");
		OutputDebugString("Assertion failed: |s.left| > 0\n");
		DebugBreak();
	}	// end if 

	ListOfT::retreat();
}	// retreat

//-------------------------------------------------------------------

void removeRightFront (produces T& x)
{
	// assert that right size > 0
	if (ListOfT::rightLength() <= 0) {
		OutputDebugString("Operation: removeRightFront\n");
		OutputDebugString("Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	ListOfT::removeRightFront(x);
}	// removeRightFront

//-------------------------------------------------------------------

T& rightFront (void)
{
	// assert that right size > 0
	if (ListOfT::rightLength() <= 0) {
		OutputDebugString("Operation: rightFront\n");
		OutputDebugString("Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	return (ListOfT::rightFront());
}	// rightFront

//-------------------------------------------------------------------

void replaceRightFront (alters T& x)
{
	// assert that right size > 0
	if (ListOfT::rightLength() <= 0) {
		OutputDebugString("Operation: replaceRightFront\n");
		OutputDebugString("Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	ListOfT::replaceRightFront(x);
}	// replaceRightFront
};

