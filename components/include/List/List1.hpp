#pragma once
/*
	Realization of List using ChainPosition
	Author: Dr. Holly
*/

#include "ChainPosition\ChainPosition.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class List1
	//! is modeled by tuple of
	//!   left: string(T)
	//!   right: string(T)
	//! exemplar self
{
public: // standard Operations
	List1 ();
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	~List1 ();
	void clear (void);
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	void transferFrom(List1& source);
		//! alters self, source
		//! ensures self = #source  and  source = < > < >
	List1& operator = (List1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// List1 Specific Operations
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
	void swapRights (List1& otherS);
		//! alters self, otherS
		//! ensures: self.left = #self.left  and  otherS.left = #otherS.left  and
		//!          otherS.right = #self.right  and  self.right = #otherS.right
	Integer leftLength (void);
		//! preserves self
		//! ensures: leftLength = |self.left|
	Integer rightLength (void);
		//! preserves self
		//! ensures: rightLength = |self.right|

	friend ostream & operator<< <T>(ostream &os, List1<T>& s);
		//! alters os
		//! preserves s

private: // representation
	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT preFront;
	ChainPositionOfT lastLeft;
	ChainPositionOfT lastNode;
	Integer lengthOfLeft;
	Integer lengthOfRight;

private: // local operations
	void createNewRep(void);

private: // disallowed List1 Operations
	List1 (const List1& s);
	List1* operator & (void) {return (this);};
	const List1* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T>
void List1<T>::createNewRep(void)
{
	T temp;

	preFront.labelNew (temp);
	lastLeft = preFront;
	lastNode = preFront;
	lengthOfLeft.clear ();
	lengthOfRight.clear ();
}

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
List1<T>::List1 ()
{
	self.createNewRep();
}	// List1

//-----------------------------------------------------------------------

template <class T>
List1<T>::~List1 ()
{
}	// ~List1

//-----------------------------------------------------------------------

template <class T>
void List1<T>::transferFrom(List1& source)
{
	preFront.transferFrom(source.preFront);
	lastLeft.transferFrom(source.lastLeft);
	lastNode.transferFrom(source.lastNode);
	lengthOfLeft.transferFrom(source.lengthOfLeft);
	lengthOfRight.transferFrom(source.lengthOfRight);
	source.createNewRep();
}

//-----------------------------------------------------------------------

template <class T>
List1<T>& List1<T>::operator = (List1& rhs)
{
	ChainPositionOfT newPos, oldPos;
	T x;

	preFront.labelNew (x);
	lastLeft = preFront;
	lastNode = preFront;

	oldPos = rhs.preFront;
	oldPos.applyTarget ();
	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		if (oldPos == rhs.lastLeft) {
			// in the rhs list we have found lastLeft location
			// set the lastLeft in the receiving list
			lastLeft = newPos;
		} // end if
		lastNode.swapWithTarget (newPos);
		lastNode.applyTarget ();
		oldPos.applyTarget ();
	} // end while
	lengthOfLeft = rhs.lengthOfLeft;
	lengthOfRight = rhs.lengthOfRight;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void List1<T>::clear (void)
{
	self.createNewRep();
}	// clear

//-----------------------------------------------------------------------

template <class T>
void List1<T>::moveToStart (void)
{
	lastLeft = preFront;
	lengthOfRight += lengthOfLeft;
	lengthOfLeft = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void List1<T>::moveToFinish (void)
{
	lastLeft = lastNode;
	lengthOfLeft += lengthOfRight;
	lengthOfRight = 0;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void List1<T>::advance (void)
{
	lastLeft.applyTarget ();
	lengthOfLeft++;
	lengthOfRight--;
}	// advance

//-----------------------------------------------------------------------

template <class T>
void List1<T>::addRightFront (T& x)
{
	ChainPositionOfT newPos;
	ChainPositionOfT temp;

	newPos.labelNew (x);
	temp = newPos;
	lastLeft.swapWithTarget (temp);
	newPos.swapWithTarget (temp);
	lengthOfRight++;
	if (lengthOfRight == 1) {
		lastNode = newPos;
	} // end if
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void List1<T>::removeRightFront (T& x)
{
	ChainPositionOfT temp;

	temp = lastLeft;
	temp.applyTarget ();
	temp.replaceLabel (x);
	temp.applyTarget ();
	lastLeft.swapWithTarget (temp);
	lengthOfRight--;
	if (lengthOfRight == 0) {
		lastNode = lastLeft;
	} // end if
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& List1<T>::rightFront(void)
{
	ChainPositionOfT temp;

	temp = lastLeft;
	temp.applyTarget ();
	return (temp.label());
}  // rightFront


//-----------------------------------------------------------------------

template <class T>
void List1<T>::replaceRightFront (T& x)
{
	ChainPositionOfT temp;

	temp = lastLeft;
	temp.applyTarget ();
	temp.replaceLabel (x);
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void List1<T>::swapRights (List1& s)
{
	ChainPositionOfT temp;

	lastLeft.swapWithTarget (temp);
	(s.lastLeft).swapWithTarget (temp);
	lastLeft.swapWithTarget (temp);

	// swap lastNodes
	temp.transferFrom(lastNode);
	lastNode.transferFrom(s.lastNode);
	s.lastNode.transferFrom(temp);

	int length = lengthOfRight;
	lengthOfRight = s.lengthOfRight;
	s.lengthOfRight = length;

	if (lengthOfRight == 0) {
		lastNode = lastLeft;
	} // end if
	if (s.lengthOfRight == 0) {
		s.lastNode = s.lastLeft;
	} // end if
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer List1<T>::leftLength (void)
{
	return (lengthOfLeft);
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
inline Integer List1<T>::rightLength (void)
{
	return (lengthOfRight);
}	// rightLength

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, List1<T>& s)
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