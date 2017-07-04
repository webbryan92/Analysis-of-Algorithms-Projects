#pragma once
/*
	Realization of TwoWayListTemplate using CyclePosition
	Author: Dr. Holly
*/

#include "CyclePosition\CyclePosition.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class TwoWayList1
	//! is modeled by tuple of
	//!   left: string(T)
	//!   right: string(T)
	//! exemplar self
{
public: // standard Operations
	TwoWayList1 ();
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	~TwoWayList1 ();
	void clear (void);
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	void transferFrom(TwoWayList1& source);
		//! alters self, source
		//! ensures self = #source  and  source = < > < >
	TwoWayList1& operator = (TwoWayList1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// TwoWayList1 Specific Operations
	void moveToStart (void);
		//! alters self
		//! ensures: self.left = < >  and  self.right = #self.left * #self.right
	void moveToFinish (void);
		//! alters self
		//! ensures: self.right = < >  and  self.left = #self.left * #self.right
	void advance (void);
		//! alters self
		//! requires: self.right /= < >
		//! ensures: self.left * self.right = #self.left * #self.right  and
		//!          |self.left| = |#self.left| + 1
	void retreat (void);
		//! alters self
		//! requires: self.left /= < >
		//! ensures: self.left * self.right = #self.left * #self.right  and
		//!          |self.right| = |#self.right| + 1
	void addRightFront (T& x);
		//! alters self
		//! consumes x
		//! ensures: self.left = #self.left  and  self.right = <#x> * #self.right
	void removeRightFront (T& x);
		//! alters self
		//! produces x
		//! requires: self.right /= < >
		//!  ensures: self.left = #self.left  and
		//!           <x> is prefix of #self.right  and 
		//!           self.right = #self.right[1,|#self.right|)
	T& rightFront(void);
		//! preserves self
		//! requires: self.right /= < >
		//!  ensures: <rightFront> is prefix of self.right
	void replaceRightFront (T& x);
		//! alters self, x
		//! requires: self.right /= < >
		//!  ensures: self.left = #self.left  and
		//!           <x> is prefix of #self.right  and
		//!           self.right = <#x> * #self.right[1, |#self.right|)
	void swapRights (TwoWayList1& otherS);
		//! alters self, otherS
		//! ensures: self.left = #self.left  and  otherS.left = #otherS.left  and
		//!          otherS.right = #self.right  and  self.right = #otherS.right
	Integer leftLength (void);
		//! preserves self
		//! ensures: leftLength = |self.left|
	Integer rightLength (void);
		//! preserves self
		//! ensures: rightLength = |self.right|

	friend ostream & operator<< <T>(ostream &os, TwoWayList1<T>& s);
		//! alters os
		//! preserves s

private: // representation
	typedef CyclePosition1 <T> CyclePositionOfT;

	CyclePositionOfT preFront;
	CyclePositionOfT lastLeft;
	Integer lengthOfLeft;
	Integer lengthOfRight;

private: // local operations
	void clearRep(void);

private: // disallowed TwoWayList1 Operations
	TwoWayList1 (const TwoWayList1& s);
	TwoWayList1* operator & (void) {return (this);};
	const TwoWayList1* operator & (void) const {return (this);};
};
//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::clearRep(void)
{
	preFront.clear();
	lastLeft.clear();
	lengthOfLeft.clear();
	lengthOfRight.clear();
} // clearRep

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
TwoWayList1<T>::TwoWayList1 ()
{
	lastLeft = preFront;
}	// TwoWayList1

//-----------------------------------------------------------------------

template <class T>
TwoWayList1<T>::~TwoWayList1 ()
{
}	// ~TwoWayList1

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::transferFrom(TwoWayList1& source)
{
	preFront.transferFrom(source.preFront);
	lastLeft.transferFrom(source.lastLeft);
	lengthOfLeft.transferFrom(source.lengthOfLeft);
	lengthOfRight.transferFrom(source.lengthOfRight);
	
	lastLeft = preFront;
}

//-----------------------------------------------------------------------

template <class T>
TwoWayList1<T>& TwoWayList1<T>::operator = (TwoWayList1& rhs)
{
	CyclePositionOfT existingPos, current;
	T x;
	Integer size;

	self.clearRep();
	lastLeft = preFront;
	current = lastLeft;

	existingPos = rhs.preFront;
	existingPos.applyTarget();
	size = rhs.lengthOfLeft + rhs.lengthOfRight;
	while (size > 0) {
		CyclePositionOfT newPos;
		x = existingPos.label();
		newPos.replaceLabel(x);
		current.transposeAfter(newPos);
		current.applyTarget();
		if (existingPos == rhs.lastLeft) {
			lastLeft = current;
		} // end if
		existingPos.applyTarget();
		size--;
	} // end while
	lengthOfLeft = rhs.lengthOfLeft;
	lengthOfRight = rhs.lengthOfRight;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::clear (void)
{
	self.clearRep();
	lastLeft = preFront;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::moveToStart (void)
{
	lastLeft = preFront;
	lengthOfRight += lengthOfLeft;
	lengthOfLeft = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::moveToFinish (void)
{
	lastLeft = preFront;
	lastLeft.applyInverseTarget();
	lengthOfLeft += lengthOfRight;
	lengthOfRight = 0;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::advance (void)
{
	lastLeft.applyTarget();
	lengthOfLeft++;
	lengthOfRight--;
}	// advance

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::retreat (void)
{
	lastLeft.applyInverseTarget();
	lengthOfLeft--;
	lengthOfRight++;
}	// retreat

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::addRightFront (T& x)
{
	CyclePositionOfT newPos;

	newPos.replaceLabel(x);
	lastLeft.transposeAfter(newPos);
	lengthOfRight++;
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::removeRightFront (T& x)
{
	CyclePositionOfT temp;

	temp = lastLeft;
	temp.applyTarget();
	temp.replaceLabel(x);
	lastLeft.transposeAfter(temp);
	lengthOfRight--;
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& TwoWayList1<T>::rightFront (void)
{
	CyclePositionOfT temp;

	temp = lastLeft;
	temp.applyTarget();
	return (temp.label());
}  // rightFront

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::replaceRightFront (T& item)
{
	CyclePositionOfT temp;

	temp = lastLeft;
	temp.applyTarget();
	temp.replaceLabel (item);
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::swapRights (TwoWayList1& s)
{
	lastLeft.transposeAfter(s.lastLeft);
	preFront.transposeBefore(s.preFront);

	int temp = lengthOfRight;
	lengthOfRight = s.lengthOfRight;
	s.lengthOfRight = temp;
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer TwoWayList1<T>::leftLength (void)
{
	return (lengthOfLeft);
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
Integer TwoWayList1<T>::rightLength (void)
{
	return (lengthOfRight);
}	// rightLength

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, TwoWayList1<T>& s)
{
	os << "<";
	int lengthOfLeft = s.leftLength();

	s.moveToStart();
	for (int i = 0, lastItem = lengthOfLeft - 1; i < lengthOfLeft; i++) {
		os << s.rightFront();
		s.advance();
		if (i < lastItem) {
			os << ",";
		} // end if
	}
	os << "> <";

	int lengthOfRight = s.rightLength();
	for (int i = 0, lastItem = lengthOfRight - 1; i < lengthOfRight; i++) {
		os << s.rightFront();
		s.advance();
		if (i < lastItem) {
			os << ",";
		} // end if
	}
	os << ">";

	// reset fence to original location
	s.moveToStart();
	for (int i = 0; i < lengthOfLeft; i++) {
		s.advance();
	}
	return (os);
}