#pragma once
//
// Exchange Sort Realization of SortingMachine using Array
// author: Dr. Holly
//

#include "CeramicArray\CeramicArray1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

class IntegerSorter5
	//! IntegerSorter5 is modeled by tuple of
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
	IntegerSorter5();
	//! alters self
	//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	~IntegerSorter5();
	void clear(void);
	//! alters self
	//! ensures: self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	void transferFrom(IntegerSorter5& source);
	//! alters self, source
	//! ensures self = #source  and  
	//!         source = self.contents = { }  and  self.inserting = true  and  self.maxSize = 0
	IntegerSorter5& operator = (IntegerSorter5& rhs);
	//! alters self
	//! preserves rhs
	//! ensures: self = rhs

	// IntegerSorter5 Specific Operations
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

	friend ostream & operator<< (ostream &os, IntegerSorter5& s);
	//! alters os
	//! preserves s

private: // representation
	typedef CeramicArray1 <Integer> ArrayOfT;

	Boolean insertionMode;
	ArrayOfT itemKeeper;
	Integer nextAddLocation;
	Integer maxContentsSize;

private: // local Operations
	//void heapSort(ArrayOfT& s, int size);
	int parent(int i);
	int left(int i);
	int right(int i);
	void heapify(ArrayOfT& s, int size, int index);
	void buildHeap(ArrayOfT& s, int size);

private: // disallowed IntegerSorter5 Operations
	IntegerSorter5(const IntegerSorter5& s);
	IntegerSorter5* operator & (void) { return (this); };
	const IntegerSorter5* operator & (void) const { return (this); };
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------



//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------
int IntegerSorter5::parent(int i) {
	return i / 2;
}
int IntegerSorter5::left(int i) {
	return 2 * i;
}
int IntegerSorter5::right(int i) {
	return 2 * i + 1;
}

/*void IntegerSorter5::heapSort(ArrayOfT& a, int size)
{
int temp;
buildHeap(a, size);
for (int i = size; i >= 1; i--) {
temp = a[1];
a[1] = a[i];
a[i] = temp;
size - 1;
heapify(a, size, 1);
}
}*/
void IntegerSorter5::heapify(ArrayOfT& a, int size, int i)
{
	/*int largest;
	int temp;
	int l = left(i);
	int r = right(i);
	if (l <= size - 1 && a[l] > a[i]) {
		largest = l;
	}
	else largest = i;
	if (r <= size - 1 && a[r] > a[largest]) {
		largest = r;
	}
	if (largest != i) {
		temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		heapify(a, size, largest);
	}*/
	int largest;
	int temp;
	int index = i;
	while (index < size / 2) {
		if (2 * index < size && a[2 * index] < a[2 * index + 1]) {
			largest = 2 * index + 1;
		}
		else {
			largest = 2 * index;
		}
		if (a[largest] > a[index]) {
			temp = a[index];
			a[index] = a[largest];
			a[largest] = temp;
			index = largest;
		}
		else {
			index = size;
		}
	}
}
void IntegerSorter5::buildHeap(ArrayOfT& a, int size) {
	for (int i = size - 1 / 2; i >= 0; i--) {
		heapify(a, size, i);
	}
}
//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------


IntegerSorter5::IntegerSorter5()
{
	insertionMode = true;
}	// IntegerSorter5

	//----------------------------------------------------------------


IntegerSorter5::~IntegerSorter5()
{
}	// ~IntegerSorter5

	//-----------------------------------------------------------------------


void IntegerSorter5::transferFrom(IntegerSorter5& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
	nextAddLocation.transferFrom(source.nextAddLocation);
	maxContentsSize.transferFrom(source.maxContentsSize);
} // transferFrom

  //-----------------------------------------------------------------------


IntegerSorter5&
IntegerSorter5::operator = (IntegerSorter5& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	nextAddLocation = rhs.nextAddLocation;
	maxContentsSize = rhs.maxContentsSize;
	return (*this);
} // operator =

  //----------------------------------------------------------------


void IntegerSorter5::clear(void)
{
	itemKeeper.clear();
	insertionMode = true;
	nextAddLocation.clear();
	maxContentsSize.clear();
}	// clear

	//----------------------------------------------------------------


void IntegerSorter5::setMaxSize(Integer maxSize)
{
	maxContentsSize = maxSize;
	itemKeeper.setBounds(0, (maxSize - 1));
}	// setMaxSize

	//----------------------------------------------------------------


Integer IntegerSorter5::maxSize(void)
{
	return maxContentsSize;
}	// maxSize

	//----------------------------------------------------------------


void IntegerSorter5::add(Integer& x)
{
	itemKeeper[nextAddLocation].transferFrom(x);
	nextAddLocation++;
}	// add

	//----------------------------------------------------------------


void IntegerSorter5::changeToExtractionMode(void)
{
	//heapSort(itemKeeper, nextAddLocation);
	buildHeap(itemKeeper, nextAddLocation - 1);
	insertionMode = false;
}	// changeToExtractionMode

	//----------------------------------------------------------------


void IntegerSorter5::removeFirst(Integer& x)
{
	x.transferFrom(itemKeeper[0]);
	itemKeeper[0].transferFrom(itemKeeper[nextAddLocation - 1]);
	nextAddLocation--;

	heapify(itemKeeper, nextAddLocation, 0);
	//x.transferFrom(itemKeeper[nextAddLocation]);	
}	// removeFirst

	//----------------------------------------------------------------


Integer IntegerSorter5::size(void)
{
	return nextAddLocation;
}	// size

	//----------------------------------------------------------------


Boolean IntegerSorter5::isInInsertionMode(void)
{
	return insertionMode;
}	// isInInsertionMode

	//----------------------------------------------------------------


Integer IntegerSorter5::remainingCapacity(void)
{
	return maxContentsSize - nextAddLocation;
}	// remainingCapacity

	//-----------------------------------------------------------------------


ostream & operator<<(ostream &os, IntegerSorter5& sm)
{
	Boolean inInsertionPhase;
	IntegerSorter5 temp;

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