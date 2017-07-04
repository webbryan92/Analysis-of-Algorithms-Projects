#pragma once

//
// realization of Set layered on ChainPosition
// author: Dr. Holly
//

#include "ChainPosition\ChainPosition.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, class TCompare>
//! Set is modeled by FiniteSet(T)
//! exemplar self
class Set1
{
public: // standard Operations
	Set1 ();
	//! alters self
	//! ensures: self = { }
	~Set1 ();
	void clear (void);
	//! alters self
	//! ensures: self = { }
	void transferFrom(Set1& source);
	//! alters self, source
	//! ensures self = #source  and  source = { }
	Set1& operator = (Set1& rhs);
	//! alters self
	//! preserves rhs
	//! ensures: self = rhs

	// Set1 Specific Operations
	void add (T& x);
	//! alters self
	//! consumes x
	//! requires: x is not in  self
	//!  ensures: self = #self union {#x}
	void remove (T& xFromClient, T& xFromSet);
	//! alters self
	//! preserves xFromClient
	//! produces xFromSet
	//! requires: xFromClient  is in  self
	//!  ensures: self = #self / {xFromSet}  and  xFromSet = xFromClient
	void removeAny (T& x);
	//! alters self
	//! produces x
	//! requires: |self| > 0
	//!  ensures: self = #self / {x}
	Boolean contains (T& x);
	//! preserves self, x
	//! ensures: contains = (x is in self)
	Integer size (void);
	//! preserves self
	//! ensures: size = |self|

	friend ostream & operator<< <T, TCompare>(ostream &os, Set1& s);
	//! alters os
	//! preserves s

private: // representation
	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT chain;
	Integer sizeOfSet;

private: // local operations
	void createNewRep(void);

private: // disallowed Set1 Operations
	Set1 (const Set1& s);
	Set1* operator & (void) {return (this);};
	const Set1* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T, class TCompare>
void Set1<T, TCompare>::createNewRep(void)
{
	ChainPositionOfT smartPosition;
	T x;

	smartPosition.labelNew (x);
	chain.transferFrom(smartPosition);
}   // createNewRep

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------


// convention: chain == smartPosition

template <class T, class TCompare>
Set1<T, TCompare>::Set1 ()
{
	createNewRep();
}	// Set1

//-----------------------------------------------------------------------

template <class T, class TCompare>
Set1<T, TCompare>::~Set1 ()
{
}	// ~Set1

//-----------------------------------------------------------------------

template <class T, class TCompare>
void Set1<T, TCompare>::transferFrom(Set1& source)
{
	chain.transferFrom(source.chain);
	sizeOfSet.transferFrom(source.sizeOfSet);

	source.createNewRep();
} // transferFrom

//-----------------------------------------------------------------------

template <class T, class TCompare>
Set1<T, TCompare>& Set1<T, TCompare>::operator = (Set1& rhs)
{
	ChainPositionOfT newPos, oldPos, current;
	T x;

	chain.labelNew (x);
	current = chain;

	oldPos = rhs.chain;
	oldPos.applyTarget ();
	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		current.swapWithTarget (newPos);
		current.applyTarget ();
		oldPos.applyTarget ();
	} // end while
	sizeOfSet = rhs.sizeOfSet;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T, class TCompare>
void Set1<T, TCompare>::clear (void)
{
	chain.clear ();
	sizeOfSet = 0;
	createNewRep();
}	// clear

//-----------------------------------------------------------------------

template <class T, class TCompare>
void Set1<T, TCompare>::add (T& x)
{
	ChainPositionOfT newPosition;
	ChainPositionOfT firstPosition;

	chain.swapWithTarget (firstPosition);

	newPosition.labelNew (x);
	newPosition.swapWithTarget (firstPosition);
	chain.swapWithTarget (newPosition);

	sizeOfSet++;
}	// add

//-----------------------------------------------------------------------

template <class T, class TCompare>
void Set1<T, TCompare>::remove (
	T& xFromClient,
	T& xFromSet
	)
{
	ChainPositionOfT trailingPosition;
	ChainPositionOfT currentPosition;

	trailingPosition = chain;
	currentPosition = trailingPosition;
	currentPosition.applyTarget ();

	while (!TCompare::areEqual (xFromClient, currentPosition.label())) {
		trailingPosition = currentPosition;
		currentPosition.applyTarget ();
	}  // end while
	currentPosition.replaceLabel (xFromSet);

	currentPosition.applyTarget ();
	trailingPosition.swapWithTarget (currentPosition);

	sizeOfSet--;
}	// remove

//-----------------------------------------------------------------------

template <class T, class TCompare>
void Set1<T, TCompare>::removeAny (T& x)
{
	ChainPositionOfT position;

	position = chain;
	position.applyTarget ();

	position.replaceLabel(x);
	position.applyTarget ();
	chain.swapWithTarget (position);

	sizeOfSet--;
}	// removeAny

//-----------------------------------------------------------------------

template <class T, class TCompare>
Boolean Set1<T, TCompare>::contains (T& x)
{
	ChainPositionOfT position;

	position = chain;
	position.applyTarget ();

	while (!position.isZero () && !TCompare::areEqual (x, position.label())) {
		position.applyTarget ();
	}	// end while

	return (!position.isZero ());
}	// contains

//-----------------------------------------------------------------------

template <class T, class TCompare>
Integer Set1<T, TCompare>::size (void)
{
	return (sizeOfSet);
}	// size

//-----------------------------------------------------------------------

template <class T, class TCompare>
ostream & operator<<(ostream &os, Set1<T, TCompare>& s)
{
	Set1<T, TCompare> temp;

	os << "{";
	for (int i = 0, z = s.size(), lastItem = z - 1; i < z; i++) {
		T x;

		s.removeAny(x);
		os << x;
		temp.add(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	} // end for
	os << "}";

	s.transferFrom(temp);
	return (os);
} // operator<<