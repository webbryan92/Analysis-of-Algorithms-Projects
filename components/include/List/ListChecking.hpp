#pragma once

/*
	Checking Version of List
	Author: Dr. Holly
*/

template <
	template <class> class List,
	class T
>
class ListChecking1:
	public List <T>
{
	typedef List <T> ListOfT;
public:

//-------------------------------------------------------------------
	
void advance (void)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString ("Operation: Advance\n");
		OutputDebugString ("Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	ListOfT::advance ();
}	// advance

//-------------------------------------------------------------------

void removeRightFront (produces T& x)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString ("Operation: removeRightFront\n");
		OutputDebugString ("Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	ListOfT::removeRightFront (x);
}	// removeRightFront

//-------------------------------------------------------------------

T& rightFront (void)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString ("Operation: rightFront\n");
		OutputDebugString ("Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	return (ListOfT::rightFront());
}	// rightFront

void replaceRightFront (T& x)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString ("Operation: replaceRightFront\n");
		OutputDebugString ("Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	ListOfT::replaceRightFront (x);
}
};



