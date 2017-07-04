#pragma once

//
// StaticArray template
// author: Dr. Holly
//

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
class StaticArray1
	//! StaticArray1 is modeled by function from integer to T
	//! constraint: for all i: integer
	//!    ((i < lowerBound) or (i > upperBound) 
	//!    implies self(i) is initialized
	//! exemplar self
{
public: // standard Operations
	StaticArray1 ();
		//! alters self
		//! ensures: for all i: integer
		//!       self(i) is initialized
	~StaticArray1 ();
	void clear (void);
		//! alters self
		//! ensures: for all i: integer
		//!       self(i) is initialized
	void transferFrom(StaticArray1& source);
		//! alters self, source
		//! ensures self = #source  and  for all i: integer source(i) is initialized
	StaticArray1& operator = (StaticArray1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// StaticArray1 Specific Operations
	void getBounds (Integer& lower, Integer& upper);
		//! preserves self
		//! produces lower, upper
		//! ensures: lower = lowerBound  and  upper = upperBound
	T& operator [] (Integer index);
		//! preserves self, index
		//! requires: index >= lowerBound  and  index <= upperBound
		//! ensures: operator [] = self(index)

	friend ostream & operator<< <T, lowerBound, upperBound>(ostream &os, StaticArray1& a);
	//! alters os
	//! preserves a

private: // representation
	T* items;   // array of T's to be allocated

private: // local Operations
	T* createNewRep(int lb, int ub);
	void reclaimRep(T* rep);

private: // disallowed StaticArray1 Operations
	StaticArray1 (const StaticArray1& s);
	StaticArray1* operator & (void) {return (this);};
	const StaticArray1* operator & (void) const {return (this);};
};
//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
T* StaticArray1<T, lowerBound, upperBound>::createNewRep(int lb, int ub)
{
	return (new T[ub - lb + 1]);
} // createNewRep

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::reclaimRep(T* rep)
{
	delete [] rep;
} // reclaimRep

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
StaticArray1<T, lowerBound, upperBound>::StaticArray1 ()
{
	items = createNewRep(lowerBound, upperBound);
}  // StaticArray1 ()

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
StaticArray1<T, lowerBound, upperBound>::~StaticArray1 ()
{
	reclaimRep(items);
}  // ~StaticArray1 ()

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::transferFrom(StaticArray1& source)
{
	reclaimRep(items);
	items = source.items;
	source.items = createNewRep(lowerBound, upperBound);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
StaticArray1<T, lowerBound, upperBound>& StaticArray1<T, lowerBound, upperBound>::operator = (StaticArray1& rhs)
{
	Integer index, size;

	size = upperBound - lowerBound + 1;
	for (index = 0; index < size; index++) {
		items[index] = rhs.items[index];
	} // end for
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::clear (void)
{
	reclaimRep(items);
	items = createNewRep(lowerBound, upperBound);
}  // clear

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::getBounds (Integer& lower, Integer& upper)
{
	lower = lowerBound;
	upper = upperBound;
}  // getBounds

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
T& StaticArray1<T, lowerBound, upperBound>::operator [] (Integer index)
{
	return (items[index - lowerBound]);
}  // operator []

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
ostream & operator<<(ostream &os, StaticArray1<T, lowerBound, upperBound>& a)
{
	Integer i, lb, ub;

	a.getBounds (lb, ub);
	os << "[";
	for (i = lb; i <= ub; i++) {
		os << a[i];
		if (i < ub) {
			os << ",";
		} // endif
	}	// end for
	os << "]";

	return (os);
} // operator<<
