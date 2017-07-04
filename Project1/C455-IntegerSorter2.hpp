#pragma once
//
// Insertion Sort Realization of SortingMachine using Array
// author: Dr. Holly
//

#include "CeramicArray\CeramicArray1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------


class IntegerSorter2
	//! IntegerSorter2 is modeled by tuple of
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
	IntegerSorter2 ();
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	~IntegerSorter2 ();
	void clear (void);
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	void transferFrom(IntegerSorter2& source);
		//! alters self, source
		//! ensures self = #source  and  
	    //!         source = self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	IntegerSorter2& operator = (IntegerSorter2& rhs);
   		//! alters self
   		//! preserves rhs
   		//! ensures: self = rhs

	// IntegerSorter2 Specific Operations
	void setMaxSize(Integer maxSize);
	//! alters self
	//! preserves maxSize
	//! requires: 0 < maxSize
	//!  ensures: self.maxSize = maxSize
	Integer maxSize(void);
	//! preserves self
	//! ensures: maxSize = self.maxSize
	void add (Integer& x);
   		//! alters self
   		//! consumes x
   		//! requires: self.inserting  and  |self.contents| < self.maxSize
   		//!  ensures: self.contents = #self.contents  union  {#x}  and
   		//!           self.inserting = true
	void changeToExtractionMode (void);
   		//! alters self
   		//! requires:  self.inserting
   		//! ensures: self.inserting = false  and  self.contents = #self.contents
	void removeFirst (Integer& x);
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
	Integer remainingCapacity(void);
	    //! preserves self
	    //! ensures: remainingCapacity  = maxSize - |self.contents|

	friend ostream & operator<< (ostream &os, IntegerSorter2& s);
	    //! alters os
	    //! preserves s

private: // representation
	typedef CeramicArray1 <Integer> ArrayOfT;

	Boolean insertionMode;
	ArrayOfT itemKeeper;
	Integer nextAddLocation;
	Integer maxContentsSize;

private: // local Operations
	void insertionSort(ArrayOfT& s, int size);

private: // disallowed IntegerSorter2 Operations
	IntegerSorter2 (const IntegerSorter2& s);
	IntegerSorter2* operator & (void) {return (this);};
	const IntegerSorter2* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------



//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------


void IntegerSorter2::insertionSort (ArrayOfT& a, int size)
{
	for (int j = 1; j < size; j++) {
		int key = a[j];
		int k = j - 1;
		while ((k >= 0) && (a[k] <= key)) {			
			a[k + 1] = a[k];
			k--;
		} // end while
		a[k + 1] = key;
	} // end for
}	// insertionSort

//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------


IntegerSorter2::IntegerSorter2 ()
{
	insertionMode = true;
}	// IntegerSorter2

//----------------------------------------------------------------


IntegerSorter2::~IntegerSorter2 ()
{
}	// ~IntegerSorter2

//-----------------------------------------------------------------------


void IntegerSorter2::transferFrom(IntegerSorter2& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
	nextAddLocation.transferFrom(source.nextAddLocation);
	maxContentsSize.transferFrom(source.maxContentsSize);
} // transferFrom

//-----------------------------------------------------------------------


IntegerSorter2& 
IntegerSorter2::operator = (IntegerSorter2& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	nextAddLocation = rhs.nextAddLocation;
	maxContentsSize = rhs.maxContentsSize;
	return (*this);
} // operator =

//----------------------------------------------------------------


void IntegerSorter2::clear (void)
{
	itemKeeper.clear();
	insertionMode = true;
	nextAddLocation.clear();
	maxContentsSize.clear();
}	// clear

//----------------------------------------------------------------


void IntegerSorter2::setMaxSize(Integer maxSize)
{
	maxContentsSize = maxSize;
	itemKeeper.setBounds(0, (maxSize - 1));
}	// setMaxSize

	//----------------------------------------------------------------


Integer IntegerSorter2::maxSize(void)
{
	return maxContentsSize;
}	// maxSize

//----------------------------------------------------------------


void IntegerSorter2::add (Integer& x)
{
	itemKeeper[nextAddLocation].transferFrom(x);
	nextAddLocation++;
}	// add

//----------------------------------------------------------------


void IntegerSorter2::changeToExtractionMode (void)
{
	insertionSort(itemKeeper, nextAddLocation);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------


void IntegerSorter2::removeFirst (Integer& x)
{
	nextAddLocation--;
	x.transferFrom(itemKeeper[nextAddLocation]);
}	// removeFirst

//----------------------------------------------------------------


Integer IntegerSorter2::size (void)
{
	return nextAddLocation; 
}	// size

//----------------------------------------------------------------


Boolean IntegerSorter2::isInInsertionMode (void)
{
   return insertionMode;
}	// isInInsertionMode

	//----------------------------------------------------------------


Integer IntegerSorter2::remainingCapacity(void)
{
	return maxContentsSize - nextAddLocation;
}	// remainingCapacity

//-----------------------------------------------------------------------


ostream & operator<<(ostream &os, IntegerSorter2& sm)
{
	Boolean inInsertionPhase;
	IntegerSorter2 temp;

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