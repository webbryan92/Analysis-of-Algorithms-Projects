#pragma once

/*
	Realization of PreemptableQueue using ChainPosition
	Author: Dr. Holly
*/

#include "ChainPosition\ChainPosition.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class PreemptableQueue1
	//! is modeled by string(T)
	//!   exemplar self
{
public: // standard Operations
	PreemptableQueue1();
		//! alters self
		//! ensures: self = < >
	~PreemptableQueue1();
	void clear(void);
		//! alters self
		//! ensures: self = < >
	void transferFrom(PreemptableQueue1& source);
		//! alters self, source
		//! ensures self = #source  and  source = < >
	PreemptableQueue1& operator =(PreemptableQueue1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// PreemptableQueue1 Specific Operations
	void enqueue(T& x);
		//! alters self
		//! consumes x
		//! ensures: self = #self * <#x>
	void dequeue(T& x);
		//! alters self
		//! produces x
		//! requires: self /= < >
		//! ensures: <x> is prefix of #self  and  
		//!          self = #self[1, |#self|)
	void inject(T& x);
		//! alters self
		//! consumes x
		//! ensures: self = <x> * #self
	void replaceFront(T& x);
		//! alters self, x
		//! requires: self /= < >
		//!  ensures: x is prefix of #self and
		//!           self = <#x> * #self[1, |#self|)
	T& front(void);
		//! preserves self
		//! requires: self /= < >
		//!  ensures: <front> is prefix of self
	Integer length(void);
		//! preserves self
		//! ensures: length = |self|

	friend ostream& operator << <T>(ostream &os, PreemptableQueue1& q);
	//! alters os
	//! preserves q

private: // internal representation
	
	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT preFront;
	ChainPositionOfT rear;
	Integer lengthOfQueue;

private: // local operations
	void createNewRep(void);

private: // disallowed PreemptableQueue1 Operations
	PreemptableQueue1(const PreemptableQueue1& s);
	PreemptableQueue1* operator &(void) {return (this);};
	const PreemptableQueue1* operator &(void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::createNewRep(void)
{
	T temp;

	preFront.labelNew(temp);
	rear = preFront;
}   // createNewRep

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
PreemptableQueue1<T>::PreemptableQueue1 ()
{
	createNewRep();
}	// PreemptableQueue1

//-----------------------------------------------------------------------

template <class T>
PreemptableQueue1<T>::~PreemptableQueue1 ()
{
}	// ~PreemptableQueue1

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::transferFrom (PreemptableQueue1& source)
{
	preFront.transferFrom(source.preFront);
	rear.transferFrom(source.rear);
	lengthOfQueue.transferFrom(source.lengthOfQueue);

	source.createNewRep();
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
PreemptableQueue1<T>& PreemptableQueue1<T>::operator = (PreemptableQueue1& rhs)
{
	T x;
	ChainPositionOfT newPos, existingPos;

	preFront.labelNew(x);
	rear = preFront;

	existingPos = rhs.preFront;
	existingPos.applyTarget();
	while (!existingPos.isZero()) {
		x = existingPos.label();
		newPos.labelNew(x);
		rear.swapWithTarget(newPos);
		rear.applyTarget();
		existingPos.applyTarget();
	} // end while
	lengthOfQueue = rhs.lengthOfQueue;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::clear (void)
{
	T temp;

	preFront.labelNew(temp);
	rear = preFront;
	lengthOfQueue = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::enqueue (T& x)
{
	ChainPositionOfT newPos;

	newPos.labelNew(x);
	rear.swapWithTarget(newPos);
	rear.applyTarget();
	lengthOfQueue++;
}	// enqueue

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::dequeue( T& x)
{
	preFront.applyTarget();
	preFront.replaceLabel(x);
	lengthOfQueue--;
}	// dequeue

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::inject(T& x)
{
	ChainPositionOfT newPreFront;
	T temp;

	preFront.replaceLabel(x);
	newPreFront.labelNew(temp);
	newPreFront.swapWithTarget(preFront);
	preFront = newPreFront;
	lengthOfQueue++;
}	// inject

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::replaceFront (T& x)
{
	ChainPositionOfT pos;
	pos = preFront;
	pos.applyTarget();
	pos.replaceLabel(x);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T>
T& PreemptableQueue1<T>::front (void)
{
	ChainPositionOfT pos;
	pos = preFront;
	pos.applyTarget();
	return (pos.label());
}  // front

//-----------------------------------------------------------------------

template <class T>
Integer PreemptableQueue1<T>::length (void)
{
	return (lengthOfQueue);
}	// length

//-----------------------------------------------------------------------

template <class T>
ostream& operator<< (ostream &os, PreemptableQueue1<T>& q)
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
} // operator<<



