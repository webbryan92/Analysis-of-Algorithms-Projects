#pragma once

/*
	Author: Dr. Holly
*/

template <class T>
class ChainPosition1
{
public: // standard Operations
	ChainPosition1 ();
	ChainPosition1 (const ChainPosition1& p);
	~ChainPosition1 ();
	void clear (void);
	void transferFrom(ChainPosition1& source);
	ChainPosition1& operator = (ChainPosition1& rhs);

public:
	Boolean operator == (ChainPosition1& rhs);
	Boolean operator != (ChainPosition1& rhs);
	void labelNew (T& label);
	T& label(void);
	void replaceLabel (T& label);
	void applyTarget (void);
	void swapWithTarget (ChainPosition1& target);
	Boolean isZero (void);

	friend ostream & operator<< <T>(ostream &os, ChainPosition1& p);
	//! alters os
	//! preserves p

private:	// representation
	class ChainPositionRecord {
	public:
		T label;
		ChainPositionRecord* target;
		unsigned long refCount;
	};
	ChainPositionRecord* rep;
	static ChainPositionRecord* zeroPosition;

private: // local Operations
	void initializeZeroPosition (void);

	void connect (
			ChainPositionRecord* &p1,
			ChainPositionRecord* p2
		);
	void disconnect (
			ChainPositionRecord* &p
		);
};	// ChainPosition1



//---------------------------------------------------------------------
// local Operations
//---------------------------------------------------------------------

template <class T>
typename ChainPosition1<T>::ChainPositionRecord*
ChainPosition1<T>::zeroPosition = NULL;

//---------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::initializeZeroPosition (void)
{
	zeroPosition = new ChainPositionRecord;
	zeroPosition->refCount = 1;
	connect (zeroPosition->target, zeroPosition);
}	// initializeZeroPosition

//---------------------------------------------------------------------

template <class T>
inline void ChainPosition1<T>::connect (
			ChainPositionRecord*& p1,
			ChainPositionRecord* p2
		)
{
	p1 = p2;
	p2->refCount++;
}	// connect

//---------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::disconnect (
			ChainPositionRecord*& p
		)
{
	ChainPositionRecord* nextP;

	p->refCount--;
	while (p->refCount == 0) {
		nextP = p->target;
		p = nextP;
		p->refCount--;
	}	// end while
}	// disconnect

//---------------------------------------------------------------------
// exported operations
//---------------------------------------------------------------------

template <class T>
ChainPosition1<T>::ChainPosition1 ()
{
	if (zeroPosition == NULL) {
   		initializeZeroPosition ();
	} // end if
	connect (rep, zeroPosition);
}	// ChainPosition1

//---------------------------------------------------------------------

template <class T>
ChainPosition1<T>::ChainPosition1 (const ChainPosition1& p) 
{
	connect (rep, p.rep);
} // // ChainPosition1

//---------------------------------------------------------------------

template <class T>
ChainPosition1<T>::~ChainPosition1 ()
{
	disconnect (rep);
}	// ~ChainPosition1

//---------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::transferFrom(ChainPosition1& source)
{
	disconnect(rep);
	connect(rep, source.rep);
	disconnect(source.rep);
	connect(source.rep, zeroPosition);
} // transferFrom

//---------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::clear (void)
{
	disconnect (rep);
	connect (rep, zeroPosition);
}	// clear

//---------------------------------------------------------------------

template <class T>
ChainPosition1<T>&
ChainPosition1<T>::operator = (ChainPosition1& rhs)
{
	disconnect (rep);
	connect (rep, rhs.rep);
	return (self);
}	// operator =

//---------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::labelNew (
			T& label
		)
{
	disconnect (rep);
	rep = new ChainPositionRecord;
	rep->refCount = 1;
	rep->label.transferFrom(label);
	connect (rep->target, zeroPosition);
}	// labelNew

//---------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::replaceLabel (T& label)
{
	T temp;

	temp.transferFrom(label);
	label.transferFrom(rep->label);
	rep->label.transferFrom(temp);
}	// replaceLabel

//-----------------------------------------------------------------------

template <class T>
T& ChainPosition1<T>::label(void)
{
   return (rep->label);
}  // label

//---------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::applyTarget (void)
{
	ChainPositionRecord* oldPositionRep;

	connect (oldPositionRep, rep);
	disconnect (rep);
	connect (rep, rep->target);
	disconnect (oldPositionRep);
}	// applyTarget

//-----------------------------------------------------------------------

template <class T>
void ChainPosition1<T>::swapWithTarget (
			ChainPosition1& target
		)
{
	ChainPositionRecord* temp;

	temp = target.rep;
	target.rep = rep->target;
	rep->target = temp;
}	// swapWithTarget

//-----------------------------------------------------------------------

template <class T>
Boolean ChainPosition1<T>::isZero (void)
{
	return (rep == zeroPosition);
}	// isZero

//-----------------------------------------------------------------------

template <class T>
Boolean ChainPosition1<T>::operator == (
			ChainPosition1& rhs
		)
{
	return (rep == rhs.rep);
}	// operator ==

//-----------------------------------------------------------------------

template <class T>
Boolean ChainPosition1<T>::operator != (
			ChainPosition1& rhs
		)
{
   return (rep != rhs.rep);
}	// operator !=

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, ChainPosition1<T>& p)
{
	ChainPosition1<T> localP = p;

	while(!localP.isZero()) {
		if(localP.isZero()) {
			os << "#0";
		} else {		
			// In the following line, subtract 1 from refCount because localP is temporarily connected to
			// the position which adds 1 to that position's refCount.
			// Subtract 1 because we want to see the position's refCount w/o the addition of localP's reference.
			os << "#" << localP.rep << ":" << "(" << localP.rep->label << "," << (localP.rep->refCount - 1) << ",#";
			ChainPosition1<T> nextP = localP;
			nextP.applyTarget();
			if (nextP.isZero()) {
				os << "0)";
			} else {
				os << localP.rep->target << ")";
			} // end if
		}
		os << endl;
		localP.applyTarget();
	} // end while

	return (os);
} // operator<<