#pragma once

/*
	Realization of Stack using ChainPosition
	Author: Dr. Holly
*/

#include "ChainPosition\ChainPosition.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class Stack1
	//! is modeled by string(T)
	//!   exemplar self
{
public: // standard Operations
	Stack1 ();
		//! alters self
		//! ensures: self = < >
	~Stack1 ();
	void clear (void);
		//! alters self
		//! ensures: self = < >
	void transferFrom(Stack1& source);
		//! alters self, source
		//! ensures self = #source  and  source = < >
	Stack1& operator = (Stack1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// Stack1 Specific Operations
	void push (T& x);
		//! alters self
		//! consumes x
		//! ensures: self = <#x> + self
	void pop (T& x);
		//! alters self
		//! produces x
		//!  ensures: <x> is prefix of #self  and
		//!           self = #self[1, |#self|)
	void replaceTop(T& x);
		//! alters self, x
		//! requires: self /= < >
		//!  ensures: <x> is prefix of #self  and
		//!           self = <#x> * #self[1, |#self|)
	T& top (void);
		//! preserves self
		//! requires: self /= < >
		//!  ensures: <top> is prefix of self
	Integer length (void);
		//! preserves self
		//! ensures: length = |self|
	
	friend ostream & operator<< <T>(ostream &os, Stack1& s);
	//! alters os
	//! preserves s

private: // representation
	typedef ChainPosition1 <T> ChainPositionOfT;
	
	ChainPositionOfT topOfStack;
	Integer lengthOfStack;

private: // disallowed Stack1 Operations
	Stack1 (const Stack1& s);
	Stack1* operator & (void) {return (this);};
	const Stack1* operator & (void) const {return (this);};
};
//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
Stack1<T>::Stack1 ()
{
}	// Stack1

//-----------------------------------------------------------------------

template <class T>
Stack1<T>::~Stack1 ()
{
}	// ~Stack1

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::transferFrom(Stack1& source)
{
	topOfStack.transferFrom(source.topOfStack);
	lengthOfStack.transferFrom(source.lengthOfStack);
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
Stack1<T>& Stack1<T>::operator = (Stack1& rhs)
{
	ChainPositionOfT newPos, oldPos, current;
	T x;

	oldPos = rhs.topOfStack;
	if (!oldPos.isZero()){
		// if rhs is not empty, set up first position in lhs
		x = oldPos.label();
		oldPos.applyTarget();
		current.labelNew(x);
		topOfStack = current;
	} else {
		// rhs is empty, clear out lhs
		topOfStack.clear ();
	} // end if

	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		current.swapWithTarget (newPos);
		current.applyTarget();
		oldPos.applyTarget ();
	} // end while
	lengthOfStack = rhs.lengthOfStack;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::clear (void)
{
   topOfStack.clear ();
   lengthOfStack = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::push (T& x)
{
	ChainPositionOfT newPos;

	newPos.labelNew (x);
	newPos.swapWithTarget (topOfStack);
	topOfStack.transferFrom(newPos);
	lengthOfStack++;
}	// push

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::pop (T& x)
{
	ChainPositionOfT oldPos;

	oldPos = topOfStack;
	topOfStack.applyTarget();
	oldPos.replaceLabel(x);
	lengthOfStack--;
}	// pop

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::replaceTop (T& x)
{
	topOfStack.replaceLabel(x);
}	// replaceTop

//-----------------------------------------------------------------------

template <class T>
T& Stack1<T>::top ()
{
   return (topOfStack.label());
}  // top

//-----------------------------------------------------------------------

template <class T>
Integer Stack1<T>::length (void)
{
	return (lengthOfStack);
}	// length

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, Stack1<T>& s)
{
	Stack1<T> temp;

	os << "<";
	for (int i = 0, z = s.length(), lastItem = z - 1; i < z; i++) {
		T x;

		os << s.top();
		s.pop(x);
		temp.push(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	} // end for
	os << ">";

	for (int i = 0, z = temp.length(); i < z; i++) {
		T x;

		temp.pop(x);
		s.push(x);
	} // end for
	return (os);
} // operator<<

