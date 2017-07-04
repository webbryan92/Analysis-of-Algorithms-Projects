#pragma once
//
// Exchange Sort Realization of SortingMachine using Array
// author: Dr. Holly
//

#include "CeramicArray\CeramicArray1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

class IntegerSorter1V2
	//! IntegerSorter1V2 is modeled by tuple of
	//!             maxSize: integer
	//!             contents:  FiniteMultiSet(Integer)
	//!             inserting: boolean
	//! exemplar self

	//! math operation IS_FIRST (
	//!          s: FiniteMultiSet(Integer),
	//!          x: Integer
	//!      ): boolean
	//!      definition
	//!          x is in s  and
	//!          for all y: Item where (y is in s)
	//!              (areOrdered (x, y))

	//! TCompare required to have an areOrdered operation:
	//! 
	//! Boolean areOrdered (Integer& lhs, Integer& rhs)
	//! preserves lhs, rhs
	//!   areOrdered returns true iff the two items compared
	//!      are in order relative to each other.
	//!   lhs stands for left hand side
	//!   rhs stands for right hand side

{
public: // standard Operations
	IntegerSorter1V2();
	//! alters self
	//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	~IntegerSorter1V2();
	void clear(void);
	//! alters self
	//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	void transferFrom(IntegerSorter1V2& source);
	//! alters self, source
	//! ensures self = #source  and  
	//!         source = self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	IntegerSorter1V2& operator = (IntegerSorter1V2& rhs);
	//! alters self
	//! preserves rhs
	//! ensures: self = rhs

// IntegerSorter1V2 Specific Operations
	void setMaxSize(Integer maxSize);
	//! alters self
	//! preserves maxSize
	//! requires: 0 < maxSize
	//!  ensures: self.maxSize = maxSize
	Integer maxSize(void);
	//! preserves self
	//! ensures: maxSize = self.maxSize
	void add(Integer& x);
	//! alters self
	//! consumes x
	//! requires: self.inserting  and  |self.contents| < self.maxSize
	//!  ensures: self.contents = #self.contents  union  {#x}  and
	//!           self.inserting = true
	void changeToExtractionMode(void);
	//! alters self
	//! requires:  self.inserting
	//! ensures: self.inserting = false  and  self.contents = #self.contents
	void removeFirst(Integer& x);
	//! alters self
	//! produces x
	//! requires: not self.inserting  and  self.contents != {}
	//!  ensures: IS_FIRST (#self.contents, x)  and
	//!           self.contents = #self.contents / {x}  and
	//!           self.inserting = false
	Integer size(void);
	//! preserves  self
	//! ensures: size = |self.contents|
	Boolean isInInsertionMode(void);
	//! preserves  self
	//! ensures:    isInInsertionMode = self.inserting
	Integer remainingCapacity(void);
	//! preserves self
	//! ensures: remainingCapacity  = maxSize - |self.contents|

	friend ostream & operator<< (ostream &os, IntegerSorter1V2& s);
	//! alters os
	//! preserves s

private: // representation
	typedef CeramicArray1 <Integer> ArrayOfT;

	Boolean insertionMode;
	ArrayOfT itemKeeper;
	Integer nextAddLocation;
	Integer maxContentsSize;

private: // local Operations
	void exchangeSort(ArrayOfT& s, int size);

private: // disallowed IntegerSorter1V2 Operations
	IntegerSorter1V2(const IntegerSorter1V2& s);
	IntegerSorter1V2* operator & (void) { return (this); };
	const IntegerSorter1V2* operator & (void) const { return (this); };
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------



//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------


void IntegerSorter1V2::exchangeSort(ArrayOfT& a, int size)
{
	Boolean sorted = false;
	int i = 0;
	while (i < size - 1 && !sorted) {
		sorted = TRUE;
		i++;
		for (int j = 0; j < size - i; j++) {
			if (a[j] > a[j + 1]) {
				int temp;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				sorted = false;
			}
		}
	}
	//*
	for (int j = 0; j < size; j++) {
		int innerLoopLimit = size - 1;
		for (int k = 0; k < innerLoopLimit; k++) {
			if (a[k] <= a[k + 1]) {
				int temp;
				temp = a[k];
				a[k] = a[k + 1];
				a[k + 1] = temp;
			} // end if
		}	// end for
	} // end for*/
}	// exchangeSort

//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------


IntegerSorter1V2::IntegerSorter1V2()
{
	insertionMode = true;
}	// IntegerSorter1V2

//----------------------------------------------------------------


IntegerSorter1V2::~IntegerSorter1V2()
{
}	// ~IntegerSorter1V2

//-----------------------------------------------------------------------


void IntegerSorter1V2::transferFrom(IntegerSorter1V2& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
	nextAddLocation.transferFrom(source.nextAddLocation);
	maxContentsSize.transferFrom(source.maxContentsSize);
} // transferFrom

//-----------------------------------------------------------------------


IntegerSorter1V2&
IntegerSorter1V2::operator = (IntegerSorter1V2& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	nextAddLocation = rhs.nextAddLocation;
	maxContentsSize = rhs.maxContentsSize;
	return (*this);
} // operator =

//----------------------------------------------------------------


void IntegerSorter1V2::clear(void)
{
	itemKeeper.clear();
	insertionMode = true;
	nextAddLocation.clear();
	maxContentsSize.clear();
}	// clear

//----------------------------------------------------------------


void IntegerSorter1V2::setMaxSize(Integer maxSize)
{
	maxContentsSize = maxSize;
	itemKeeper.setBounds(0, (maxSize - 1));
}	// setMaxSize

	//----------------------------------------------------------------


Integer IntegerSorter1V2::maxSize(void)
{
	return maxContentsSize;
}	// maxSize

//----------------------------------------------------------------


void IntegerSorter1V2::add(Integer& x)
{
	itemKeeper[nextAddLocation].transferFrom(x);
	nextAddLocation++;
}	// add

//----------------------------------------------------------------


void IntegerSorter1V2::changeToExtractionMode(void)
{
	exchangeSort(itemKeeper, nextAddLocation);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------


void IntegerSorter1V2::removeFirst(Integer& x)
{
	nextAddLocation--;
	x.transferFrom(itemKeeper[nextAddLocation]);
}	// removeFirst

//----------------------------------------------------------------


Integer IntegerSorter1V2::size(void)
{
	return nextAddLocation;
}	// size

//----------------------------------------------------------------


Boolean IntegerSorter1V2::isInInsertionMode(void)
{
	return insertionMode;
}	// isInInsertionMode

	//----------------------------------------------------------------


Integer IntegerSorter1V2::remainingCapacity(void)
{
	return maxContentsSize - nextAddLocation;
}	// remainingCapacity

//-----------------------------------------------------------------------


ostream & operator<<(ostream &os, IntegerSorter1V2& sm)
{
	Boolean inInsertionPhase;
	IntegerSorter1V2 temp;

	inInsertionPhase = sm.isInInsertionMode();
	temp.setMaxSize(sm.maxSize());
	if (inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
	os << "({";
	for (int i = 0, z = sm.size(), lastItem = z - 1; i < z; i++) {
		Integer x;

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