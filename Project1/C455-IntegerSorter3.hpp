#pragma once
//
// Merge Sort Realization of SortingMachine using Array
// author: *** place your name here ***
//

#include "CeramicArray\CeramicArray1.hpp"
#include <limits.h>

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------


class IntegerSorter3
	//! IntegerSorter3 is modeled by tuple of
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
	IntegerSorter3 ();
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	~IntegerSorter3 ();
	void clear (void);
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	void transferFrom(IntegerSorter3& source);
		//! alters self, source
		//! ensures self = #source  and  
	    //!         source = self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	IntegerSorter3& operator = (IntegerSorter3& rhs);
   		//! alters self
   		//! preserves rhs
   		//! ensures: self = rhs

	// IntegerSorter3 Specific Operations
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

	friend ostream & operator<< (ostream &os, IntegerSorter3& s);
	    //! alters os
	    //! preserves s

private: // representation
	typedef CeramicArray1 <Integer> ArrayOfT;

	Boolean insertionMode;
	ArrayOfT itemKeeper;
	Integer currentAddLocation;
	Integer maxContentsSize;

private: // local Operations
	void merge(ArrayOfT& a, int p, int q, int r);
	void mergeSort(ArrayOfT& a, int p, int r);

private: // disallowed IntegerSorter3 Operations
	IntegerSorter3 (const IntegerSorter3& s);
	IntegerSorter3* operator & (void) {return (this);};
	const IntegerSorter3* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------



//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------


void IntegerSorter3::merge(ArrayOfT& a, int p, int q, int r)
{
	// TODO: implement merge using Cormen's pseudo code algorithm
	int n1 = q - p + 1;
	int n2 = r - q;
	int max = INT_MAX;
	ArrayOfT L;
	ArrayOfT R;
	L.setBounds(1, n1 + 1);
	R.setBounds(1, n2 + 1);
	for (int i = 1; i <= n1; i++) {
		L[i] = a[p + i - 1];
	}
	for (int i = 1; i <= n1; i++) {
		R[i] = a[q + i];
	}
	L[n1 + 1] = max;
	R[n2 + 1] = max;
	int i = 1;
	int j = 1;
	for (int k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i = i + 1;
		}
		else {
			a[k] = R[j];
			j = j + 1;
		}
	}
}	// merge


	//----------------------------------------------------------------


void IntegerSorter3::mergeSort(ArrayOfT& a, int p, int r)
{
	// TODO: implement mergeSort using Cormen's pseudo code algorithm
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(a, p, q);
		mergeSort(a, q + 1, r);
		merge(a, p, q, r);
	}
}	// mergeSort

//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------


IntegerSorter3::IntegerSorter3 ()
{
	insertionMode = true;
}	// IntegerSorter3

//----------------------------------------------------------------


IntegerSorter3::~IntegerSorter3 ()
{
}	// ~IntegerSorter3

//-----------------------------------------------------------------------


void IntegerSorter3::transferFrom(IntegerSorter3& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
	currentAddLocation.transferFrom(source.currentAddLocation);
	maxContentsSize.transferFrom(source.maxContentsSize);
} // transferFrom

//-----------------------------------------------------------------------


IntegerSorter3& 
IntegerSorter3::operator = (IntegerSorter3& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	currentAddLocation = rhs.currentAddLocation;
	maxContentsSize = rhs.maxContentsSize;
	return (*this);
} // operator =

//----------------------------------------------------------------


void IntegerSorter3::clear (void)
{
	itemKeeper.clear();
	insertionMode = true;
	currentAddLocation.clear();
	maxContentsSize.clear();
}	// clear

//----------------------------------------------------------------


void IntegerSorter3::setMaxSize(Integer maxSize)
{
	maxContentsSize = maxSize;
	itemKeeper.setBounds(1, maxSize);
}	// setMaxSize

	//----------------------------------------------------------------


Integer IntegerSorter3::maxSize(void)
{
	return maxContentsSize;
}	// maxSize

//----------------------------------------------------------------


void IntegerSorter3::add (Integer& x)
{
	currentAddLocation++;
	itemKeeper[currentAddLocation].transferFrom(x);
}	// add

//----------------------------------------------------------------


void IntegerSorter3::changeToExtractionMode (void)
{
	mergeSort(itemKeeper, 1, currentAddLocation);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------


void IntegerSorter3::removeFirst (Integer& x)
{
	x.transferFrom(itemKeeper[currentAddLocation]);
	currentAddLocation--;
}	// removeFirst

//----------------------------------------------------------------


Integer IntegerSorter3::size (void)
{
	return currentAddLocation; 
}	// size

//----------------------------------------------------------------


Boolean IntegerSorter3::isInInsertionMode (void)
{
   return insertionMode;
}	// isInInsertionMode

	//----------------------------------------------------------------


Integer IntegerSorter3::remainingCapacity(void)
{
	return maxContentsSize - currentAddLocation;
}	// remainingCapacity

//-----------------------------------------------------------------------


ostream & operator<<(ostream &os, IntegerSorter3& sm)
{
	Boolean inInsertionPhase;
	IntegerSorter3 temp;

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