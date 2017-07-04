#pragma once

/*
	Realization of Queue using OneWayList
	Author: Dr. Holly
*/

#include "List\List1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class Queue2
	//! is modeled by string(T)
	//!   exemplar self
{
public: // standard Operations
	Queue2 ();
		//! alters self
		//! ensures: self = < >
	~Queue2 ();
	void clear (void);
		//! alters self
		//! ensures: self = < >
	void transferFrom (Queue2& source);
		//! alters self, source
		//! ensures self = #source  and  source = < >
	Queue2& operator = (Queue2& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// Queue2 Specific Operations
	void enqueue (T& x);
		//! alters self
		//! consumes x
		//! ensures: self = #self * <#x>
	void dequeue (T& x);
		//! alters self
		//! produces x
		//! requires: self /= < >
		//! ensures: <x> is prefix of #self  and  
		//!          self = #self[1,|#self|)
	void replaceFront (T& x);
		//! alters self, x
		//! requires: self /= < >
		//!  ensures: x is prefix of #self and
		//!           self = <#x> * #self[1,|#self|)
	T& front (void);
		//! preserves self
		//! requires: self /= < >
		//!  ensures: <front> is prefix of self
	Integer length (void);
		//! preserves self
		//! ensures: length = |self|

	friend ostream & operator<< <T> (ostream &os, Queue2<T>& q);
	//! alters os
	//! preserves q

private:// internal Representation

	typedef List1 <T> ListOfT;

	ListOfT s;

private: // disallowed Queue2 Operations
	Queue2(Queue2& actual);
	Queue2* operator &(void) {return(this);};
	const Queue2* operator &(void) const {return(this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

// leave Queue's copy constructor unimplemented.
// client cannot call it because it is a private member.
template <class T>
Queue2<T>::Queue2(Queue2& actual)
{
}	// Queue2

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
Queue2<T>::Queue2()
{
}	// Queue2

//-----------------------------------------------------------------------

template <class T>
Queue2<T>::~Queue2()
{
}	// ~Queue2

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::transferFrom (Queue2& source)
{
	s.transferFrom(source.s);
}

//-----------------------------------------------------------------------

template <class T>
Queue2<T>& Queue2<T>::operator = (Queue2& rhs)
{
	s = rhs.s;
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::clear (void)
{
	s.clear();
}	// clear


//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::enqueue (T& x)
{
	s.moveToFinish();
	s.addRightFront(x);
}	// enqueue

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::dequeue (T& x)
{
	s.moveToStart();
	s.removeRightFront(x);
}	// dequeue

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::replaceFront(T& x)
{
	s.moveToStart();
	s.replaceRightFront(x);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T>
T& Queue2<T>::front (void)
{
	s.moveToStart();
	return (s.rightFront());
}  // front

//-----------------------------------------------------------------------

template <class T>
Integer Queue2<T>::length (void)
{
	return (s.leftLength() + s.rightLength());
}	// size

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, Queue2<T>& q)
{
	os << "<";
	for (int i = 0, z = q.length(), lastItem = z - 1; i < z; i++) {
		T x;

		q.dequeue(x);
		os << x;
		q.enqueue(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	} // end for
	os << ">";
	return (os);
}