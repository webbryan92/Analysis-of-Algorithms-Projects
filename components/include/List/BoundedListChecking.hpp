#pragma once

/*
	Checking Version of BoundedList
	Author: Dr. Holly
*/

template <
	template <class, int> class BoundedList,
	class T,
	int maxLength
>
class BoundedListChecking1:
	public BoundedList <T, maxLength>
{
	typedef BoundedList <T, maxLength> ListOfT;
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

void addRightFront(produces T& x)
{
	// assert that |self.left| + |self.right| + 1 <= maxLength
	if ((ListOfT::leftLength() + ListOfT::rightLength() + 1) > maxLength) {
		OutputDebugString("Operation: addRightFront\n");
		OutputDebugString("Assertion failed: |self.left| + |self.right| + 1 <= maxLength\n");
		DebugBreak();
	}	// end if 

	ListOfT::addRightFront(x);
}	// addRightFront

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

void swapRights(BoundedList1& otherS)
{
	// assert that |self.left| + |otherS.right| <= maxLength  and
    //             |otherS.left| + |self.right| <= maxLength
	if ((ListOfT::leftLength() + otherS.rightLength()) > maxLength) {
		OutputDebugString("Operation: swapRights\n");
		OutputDebugString("Assertion failed: |self.left| + |otherS.right| <= maxLength\n");
		DebugBreak();
	}	// end if 
	if ((otherS.leftLength() + ListOfT::rightLength()) > maxLength) {
		OutputDebugString("Operation: swapRights\n");
		OutputDebugString("Assertion failed: |otherS.left| + |self.right| <= maxLength\n");
		DebugBreak();
	}	// end if 

	ListOfT::swapRights(otherS);
}

};



