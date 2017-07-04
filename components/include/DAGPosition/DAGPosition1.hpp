#pragma once

/*
	Implementation of DagPosition using raw nodes and pointers
	Author: Dr. Holly
*/

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, int maxDirections>
class DagPosition1
{
public: // standard Operations
	DagPosition1 ();
	~DagPosition1 ();
	DagPosition1 (const DagPosition1& p);
	void clear (void);
	void transferFrom(DagPosition1& source);
	DagPosition1& operator = (DagPosition1& x);

	// DagPosition1 Specific Operations
	Boolean operator == (DagPosition1& rhs);
	Boolean operator != (DagPosition1& rhs);
	Integer maxDirection (void);
	void labelNew (T& label);
	void replaceLabel (T& label);
	T& label (void);
	void applyTarget (Integer direction);
	void swapWithTarget (Integer direction, DagPosition1& target);
	Boolean isZero (void);

	friend ostream & operator<< <T, maxDirections>(ostream &os, DagPosition1& p);
	//! alters os
	//! preserves p

private:	// representation
	class DagPositionRecord {
	public:
		T label;
		DagPositionRecord* target[2];
		LongInteger refCount;
	};
	DagPositionRecord* rep;
	static DagPositionRecord* zeroPosition;

private: // local Operations
	void initializeZeroPosition (void);

	void connect (
			DagPositionRecord* &p1,
			DagPositionRecord* p2
		);
	void disconnect (
			DagPositionRecord* &p
		);
	Integer getHeight (DagPositionRecord* p);
	void displayRepHelp (
			ostream &os,
			DagPositionRecord*& p
		);

private: // disallowed DagPosition1 Operations
	DagPosition1* operator & (void) {return (this);};
	const DagPosition1* operator & (void) const {return (this);};
};	// DagPosition1

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------


//---------------------------------------------------------------------
// local Operations
//---------------------------------------------------------------------


template <class T, int maxDirections>
typename DagPosition1<T, maxDirections>::DagPositionRecord*
DagPosition1<T, maxDirections>::zeroPosition = NULL;

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::initializeZeroPosition (void)
{
	zeroPosition = new DagPositionRecord;
	zeroPosition->refCount = 1;
	for (int direction = 0; direction < maxDirections; direction++) {
		connect (zeroPosition->target[direction], zeroPosition);
	}	// end for
}	// initializeZeroPosition

//---------------------------------------------------------------------

template <class T, int maxDirections>
inline void DagPosition1<T, maxDirections>::connect (
			DagPositionRecord*& p1,
			DagPositionRecord* p2
		)
{
	p1 = p2;
	p2->refCount++;
}	// connect

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::disconnect (
			DagPositionRecord*& p
		)
{
	p->refCount--;
	if (p->refCount == 0) {
		for (int direction = 0; direction < maxDirections; direction++) {
			disconnect (p->target[direction]);
		}	// end for
		delete (p);
	}	// end if
}	// disconnect

//-----------------------------------------------------------------------

template <class T, int maxDirections>
Integer DagPosition1<T, maxDirections>::getHeight (DagPositionRecord* p)
{
	Integer height, heightLeft, heightRight, directionHeight;

	if (p != zeroPosition) {
		for (int direction = 0; direction < maxDirections; direction++) {
			directionHeight = getHeight(p->target[direction]);
			if (directionHeight > height) {
				height = directionHeight;
			} // end if
		} // end for
		height++;
	} // end if
	return height;
} // getHeight

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::displayRepHelp (
		ostream &os,
		DagPositionRecord*& p
	)
{
	Integer height = getHeight(p);
	if (height == 0) {
		os << "()";
	} else {

		// preorder - display root
		os << "([" << p->label << " H: " << right << setw(2) << height << "]";
		for (int direction = 0; direction < maxDirections; direction++) {
			os << ",";
			displayRepHelp (os, p->target[direction]);
		} // end for
		os << ")";
	} // end if
} // displayRepHelp

//---------------------------------------------------------------------
// exported operations
//---------------------------------------------------------------------

template <class T, int maxDirections>
DagPosition1<T, maxDirections>::DagPosition1 ()
{
	if (zeroPosition == NULL) {
   		initializeZeroPosition ();
	} // end if
	connect (rep, zeroPosition);
}	// DagPosition1

//---------------------------------------------------------------------

template <class T, int maxDirections>
DagPosition1<T, maxDirections>::DagPosition1 (const DagPosition1& p) 
{
	connect (rep, p.rep);
} // // DagPosition1

//---------------------------------------------------------------------

template <class T, int maxDirections>
DagPosition1<T, maxDirections>::~DagPosition1 ()
{
	disconnect (rep);
}	// ~DagPosition1

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::transferFrom(DagPosition1& source)
{
	disconnect(rep);
	connect(rep, source.rep);
	disconnect(source.rep);
	connect(source.rep, zeroPosition);
} // transferFrom

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::clear (void)
{
	disconnect (rep);
	connect (rep, zeroPosition);
}	// clear

//---------------------------------------------------------------------

template <class T, int maxDirections>
DagPosition1<T, maxDirections>&
DagPosition1<T, maxDirections>::operator = (
			DagPosition1& rhs
		)
{
	disconnect (rep);
	connect (rep, rhs->rep);
	return (self);
}	// operator =

//---------------------------------------------------------------------

template <class T, int maxDirections>
Integer DagPosition1<T, maxDirections>::maxDirection (void)
{
	return (maxDirections);
}	// maxDirection

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::labelNew (
			T& label
		)
{
	disconnect (rep);
	rep = new DagPositionRecord;
	rep->refCount = 1;
	rep->label.transferFrom(label);
	for (int direction = 0; direction < maxDirections; direction++) {
		connect (rep->target[direction], zeroPosition);
	}	// end for
}	// labelNew

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::replaceLabel (
			T& label
		)
{
	T temp;

	temp.transferFrom(label);
	label.transferFrom(rep->label);
	rep->label.transferFrom(temp);
}	// replaceLabel

//-----------------------------------------------------------------------

template <class T, int maxDirections>
T& DagPosition1<T, maxDirections>::label (void)
{
   return (rep->label);
}  // label

//---------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::applyTarget (
			Integer direction
		)
{
	DagPositionRecord* oldPositionRep;

	connect (oldPositionRep, rep);
	disconnect (rep);
	connect (rep, rep->target[direction]);
	disconnect (oldPositionRep);
}	// applyTarget

//-----------------------------------------------------------------------

template <class T, int maxDirections>
void DagPosition1<T, maxDirections>::swapWithTarget (
			Integer direction,
			DagPosition1& target
		)
{
	DagPositionRecord* temp;

	temp = target.rep;
	target.rep = rep->target[direction];
	rep->target[direction] = temp;
}	// swapWithTarget

//-----------------------------------------------------------------------

template <class T, int maxDirections>
Boolean DagPosition1<T, maxDirections>::isZero (void)
{
	return (rep == zeroPosition);
}	// isZero

//-----------------------------------------------------------------------

template <class T, int maxDirections>
Boolean DagPosition1<T, maxDirections>::operator == (
			DagPosition1& rhs
		)
{
	return (rep == rhs->rep);
}	// operator ==

//-----------------------------------------------------------------------

template <class T, int maxDirections>
Boolean DagPosition1<T, maxDirections>::operator != (
			DagPosition1& rhs
		)
{
	return (rep != rhs->rep);
}	// operator !=


//-----------------------------------------------------------------------

template <class T, int maxDirections>
ostream & operator<<(ostream &os, DagPosition1<T, maxDirections>& p)
{
	p.displayRepHelp(os, p.rep);
	return (os);
} // operator<<