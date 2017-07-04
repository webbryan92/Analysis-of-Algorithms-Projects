#pragma once
//
// exchange Sort Realization of SortingMachine using List
// author: Dr. Holly
//

#include "List\List1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, class TCompare>
class SortingMachine1
	//! SortingMachine1 is modeled by tuple of
	//!             contents:  FiniteMultiSet(T)
	//!             inserting: boolean
	//! exemplar self

	//! math operation IS_FIRST (
	//!          s: FiniteMultiSet(T),
	//!          x: T
	//!      ): boolean
	//!      definition
	//!          x is in s  and
	//!          for all y: Item where (y is in s)
	//!              (areOrdered (x, y))

	//! TCompare required to have an areOrdered operation:
	//! 
	//! Boolean areOrdered (T& lhs, T& rhs)
	//! preserves lhs, rhs
	//!   areOrdered returns true iff the two items compared
	//!      are in order relative to each other.
	//!   lhs stands for left hand side
	//!   rhs stands for right hand side

{
public: // standard Operations
	SortingMachine1 ();
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true
	~SortingMachine1 ();
	void clear (void);
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true
	void transferFrom(SortingMachine1& source);
		//! alters self, source
		//! ensures self = #source  and  source = self.contents = { }  and  self.inserting = true
	SortingMachine1& operator = (SortingMachine1& rhs);
   		//! alters self
   		//! preserves rhs
   		//! ensures: self = rhs

	// SortingMachine1 Specific Operations
	void add (T& x);
   		//! alters    self
   		//! consumes x
   		//! requires: self.inserting
   		//!  ensures: self.contents = #self.contents  union  {#x}  and
   		//!           self.inserting = true
	void changeToExtractionMode (void);
   		//! alters self
   		//! requires:  self.inserting
   		//! ensures: self.inserting = false  and  self.contents = #self.contents
	void removeFirst (T& x);
   		//! alters self
   		//! produces x
   		//! requires: not self.inserting  and  self.contents != {}
   		//!  ensures: IS_FIRST (#self.contents, x)  and
   		//!           self.contents = #self.contents / {x}  and
   		//!           self.inserting = false
	Integer size (void);
   		//! preserves  self
   		//! ensures: size = |self.contents|
	Boolean isInInsertionMode (void);
   		//! preserves  self
   		//! ensures:    isInInsertionMode = self.inserting

	friend ostream & operator<< <T, TCompare>(ostream &os, SortingMachine1& s);
	//! alters os
	//! preserves s

private: // representation
	typedef List1 <T> ListOfT;

	Boolean insertionMode;
	ListOfT itemKeeper;

private: // local Operations
	void exchangeSort (alters ListOfT& s);

private: // disallowed SortingMachine1 Operations
	SortingMachine1 (const SortingMachine1& s);
	SortingMachine1* operator & (void) {return (this);};
	const SortingMachine1* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

// convention
// itemKeeper.left = < >
//

//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine1<T, TCompare>::exchangeSort (ListOfT& s)
{
	for (int i = 0, z = s.rightLength(); i < z; i++) {
		T x;
		s.removeRightFront(x);
		for (int k = 0; k < (z - 1); k++) {
			T y;
			s.removeRightFront(y);
			if (TCompare::areOrdered(x, y)) {
				s.addRightFront(x);
				x.transferFrom(y);
			}
			else {
				s.addRightFront(y);
			} // end if
			s.advance();
		}	// end for
		s.addRightFront(x);
		s.moveToStart();
	} // end for
}	// exchangeSort

//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------

template <class T, class TCompare>
SortingMachine1<T, TCompare>::SortingMachine1 ()
{
	insertionMode = true;
}	// SortingMachine1

//----------------------------------------------------------------

template <class T, class TCompare>
SortingMachine1<T, TCompare>::~SortingMachine1 ()
{
}	// ~SortingMachine1

//-----------------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine1<T, TCompare>::transferFrom(SortingMachine1& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, class TCompare>
SortingMachine1<T, TCompare>& 
SortingMachine1<T, TCompare>::operator = (SortingMachine1& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	return (*this);
} // operator =

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine1<T, TCompare>::clear (void)
{
	itemKeeper.clear();
	insertionMode = true;
}	// clear

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine1<T, TCompare>::add (T& x)
{
	itemKeeper.addRightFront(x);
}	// add

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine1<T, TCompare>::changeToExtractionMode (void)
{
	exchangeSort(itemKeeper);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine1<T, TCompare>::removeFirst (T& x)
{
	itemKeeper.removeRightFront(x);
}	// removeFirst

//----------------------------------------------------------------

template <class T, class TCompare>
Integer SortingMachine1<T, TCompare>::size (void)
{
   return (itemKeeper.rightLength());
}	// size

//----------------------------------------------------------------

template <class T, class TCompare>
Boolean SortingMachine1<T, TCompare>::isInInsertionMode (void)
{
   return (insertionMode);
}	// isInInsertionMode

//-----------------------------------------------------------------------

template <class T, class TCompare>
ostream & operator<<(ostream &os, SortingMachine1<T, TCompare>& sm)
{
	Boolean inInsertionPhase;
	SortingMachine1<T, TCompare> temp;

	inInsertionPhase = sm.isInInsertionMode();
	if (inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
	os << "({";
	for (int i = 0, z = sm.size(), lastItem = z - 1; i < z; i++) {
		T x;

		sm.removeFirst(x);
		os << x;
		temp.add(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	}	// end for
	os << "},";
	os << inInsertionPhase << ")";

	sm.transferFrom(temp);
	if (!inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
	return (os);
} // operator<<