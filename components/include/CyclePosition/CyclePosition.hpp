#pragma once

/*
	Implementation of Cycle Position raw nodes & pointers
	Author: Dr. Holly
*/

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class CyclePosition1
{
public: // standard Operations
	CyclePosition1 ();
	~CyclePosition1 ();
	void clear (void);
	void transferFrom(CyclePosition1& source);
	CyclePosition1& operator = (CyclePosition1& rhs);

	// CyclePosition1 Specific Operations
	Boolean operator == (CyclePosition1& rhs);
	Boolean operator != (CyclePosition1& rhs);
	void labelNew (T& label);
	T& label (void);
	void replaceLabel (T& label);
	void applyTarget (void);
	void applyInverseTarget (void);
	void transposeBefore (CyclePosition1& p2);
	void transposeAfter (CyclePosition1& p2);
	void swapWithTarget (CyclePosition1& position);

	// static void displayMemoryAllocation (void);

	void displayRep (void);

private:	// representation
	class NodeRecord {
	public:
		T label;
		NodeRecord* predTarget;
		NodeRecord* succTarget;
	};

	class CyclePositionRecord {
	public:
		unsigned long refCount;
		CyclePositionRecord* predTarget;
		CyclePositionRecord* succTarget;
		NodeRecord* nodeTarget;
	};
	CyclePositionRecord* rep;

private: // local Operations
	void allocate(CyclePositionRecord*& p);
	void allocate(NodeRecord*& n);
	void connect(CyclePositionRecord*& p1, CyclePositionRecord* p2);
	void disconnect(CyclePositionRecord*& p);

	void displayCyclePosition (CyclePositionRecord*& p);


private: // disallowed CyclePosition1 Operations
	CyclePosition1 (CyclePosition1& x);
	CyclePosition1* operator & (void) {return (this);};
	const CyclePosition1* operator & (void) const {return (this);};
};	// CyclePosition1

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//---------------------------------------------------------------------
// local Operations
//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::allocate(CyclePositionRecord*& p)
//  pre: p = NULL  or  p = undefined
// post: 
{
	p = new CyclePositionRecord;
	p->refCount = 1;
	p->predTarget = p;
	p->succTarget = p;
	p->nodeTarget = NULL;
}	// allocate

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::allocate(NodeRecord*& n)
//  pre: n = NULL  or  p = undefined
{
	n = new NodeRecord;
	n->predTarget = n;
	n->succTarget = n;
}	// allocate

//---------------------------------------------------------------------

template <class T>
inline void CyclePosition1<T>::connect(
			CyclePositionRecord*& p1,
			CyclePositionRecord* p2
		)
{
	p1 = p2;
	p2->refCount++;
}	// connect

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::disconnect(CyclePositionRecord*& p)
{
	p->refCount--;
	if (p->refCount == 0) {
		if (p->succTarget == p) {
			NodeRecord* q;
			NodeRecord* oldNode;

			// p is the last Position to have access to this linked sturcture.
			//
			// must break cycle in linked sturcture.
			rep->nodeTarget->predTarget->succTarget = NULL;
			// traverse linked nodes and deallocate.
			oldNode = rep->nodeTarget;
			do {
				q = oldNode->succTarget;
				delete oldNode;
				oldNode = q;
			} while (oldNode != NULL);
		} else {
			// there are other Positions that have access to this
			// linked structure, just take p out of the chain.
			(p->succTarget)->predTarget = p->predTarget;
			(p->predTarget)->succTarget = p->succTarget;
		}	// end if
		delete p;
	}	// end if
}	// disconnect

//---------------------------------------------------------------------
// exported operations
//---------------------------------------------------------------------

template <class T>
CyclePosition1<T>::CyclePosition1 ()
{
	allocate(rep);
	allocate(rep->nodeTarget);
}	// CyclePosition1

//---------------------------------------------------------------------

template <class T>
CyclePosition1<T>::~CyclePosition1 ()
{
	disconnect(rep);
}	// ~CyclePosition1

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::transferFrom(CyclePosition1& source)
{
	disconnect(rep);
	connect(rep, source.rep);
	disconnect(source.rep);
	allocate(source.rep);
	allocate(source.rep->nodeTarget);
} // transferFrom

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::clear (void)
{
	disconnect(rep);
	allocate(rep);
	allocate(rep->nodeTarget);
}	// clear

//---------------------------------------------------------------------

template <class T>
CyclePosition1<T>& CyclePosition1<T>::operator = (CyclePosition1& rhs)
{
	disconnect(rep);
	connect(rep, rhs.rep);
	return (self);
}	// operator =

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::labelNew (T& label)
{
	disconnect(rep);
	allocate(rep);
	allocate(rep->nodeTarget);
	rep->nodeTarget->label.transferFrom(label);
}	// labelNew

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::replaceLabel (T& label)
{
	T temp;

	temp.transferFrom(label);
	label.transferFrom(rep->nodeTarget->label);
	rep->nodeTarget->label.transferFrom(temp);
}	// replaceLabel

//-----------------------------------------------------------------------

template <class T>
T& CyclePosition1<T>::label (void)
{
   return (rep->nodeTarget->label);
}  // label

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::applyTarget (void)
{
	CyclePositionRecord* oldP;

	if (rep->nodeTarget->succTarget == (rep->succTarget)->nodeTarget) {
		// there already exists a Position for the successor Node.
		connect(oldP, rep);
		disconnect(rep);
		connect(rep, oldP->succTarget);
		disconnect(oldP);
	} else {
		// there doesn't exist a Position for the successor Node.
		if (rep->refCount == 1) {
			// and no other Position variables use this Position Node.
			// move this Position to the successor node.
			rep->nodeTarget = rep->nodeTarget->succTarget;
		} else {
			// refCount > 1
			// other Position variables use this Position Node, make
			// a new Position node for successor Node.
			connect(oldP, rep);
			disconnect(rep);
			allocate(rep);
			rep->nodeTarget = oldP->nodeTarget->succTarget;
			rep->succTarget = oldP->succTarget;
			rep->predTarget = oldP;
			(oldP->succTarget)->predTarget = rep;
			oldP->succTarget = rep;
			disconnect(oldP);
		}	// end if
	}	// end if
}	// applyTarget

//---------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::applyInverseTarget (void)
{
	CyclePositionRecord* oldP;

	if (rep->nodeTarget->predTarget == (rep->predTarget)->nodeTarget) {
		// there already exists a Position for the predecessor Node.
		connect(oldP, rep);
		disconnect(rep);
		connect(rep, oldP->predTarget);
		disconnect(oldP);
	} else {
		if (rep->refCount == 1) {
			// no other Position variables use this Position Node,
			// link it to the predecessor Node.
			rep->nodeTarget = rep->nodeTarget->predTarget;
		} else {
			// refCount > 1
			// other Position variables use this Position Node, make
			// a new Position node for predecessor Node.
			connect(oldP, rep);
			disconnect(rep);
			allocate(rep);
			rep->nodeTarget = oldP->nodeTarget->predTarget;
			rep->succTarget = oldP;
			rep->predTarget = oldP->predTarget;
			(oldP->predTarget)->succTarget = rep;
			oldP->predTarget = rep;
			disconnect(oldP);
		}	// end if
	}	// end if
}	// applyInverseTarget

//-----------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::transposeBefore (preserves CyclePosition1& p2)
{
	CyclePositionRecord* tempPosition;
	NodeRecord* tempNode;

	// adjust Positions p1 and p2.
	// adjust successor targets.
	rep->predTarget->succTarget = p2.rep;
	p2.rep->predTarget->succTarget = rep;
	// adjust predecessor targets.
	tempPosition = rep->predTarget;
	rep->predTarget = p2.rep->predTarget;
	p2.rep->predTarget = tempPosition;

	// adjust Nodes pointed to by Positions p1 and p2.
	// adjust successor targets.
	rep->nodeTarget->predTarget->succTarget =
		p2.rep->nodeTarget;
	p2.rep->nodeTarget->predTarget->succTarget =
		rep->nodeTarget;
	// adjust predecessor targets.
	tempNode = rep->nodeTarget->predTarget;
	rep->nodeTarget->predTarget =
		p2.rep->nodeTarget->predTarget;
	p2.rep->nodeTarget->predTarget = tempNode;
} // transposeBefore

//-----------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::transposeAfter (preserves CyclePosition1& p2)
{
	CyclePositionRecord* tempPosition;
	NodeRecord* tempNode;

	// adjust Positions rep and p2.
	// adjust predecessor targets.
	rep->succTarget->predTarget = p2.rep;
	p2.rep->succTarget->predTarget = rep;
	// adjust successor targets.
	tempPosition = rep->succTarget;
	rep->succTarget = p2.rep->succTarget;
	p2.rep->succTarget = tempPosition;

	// adjust Nodes pointed to by Positions rep and p2.
	// adjust predecessor targets.
	rep->nodeTarget->succTarget->predTarget =
		p2.rep->nodeTarget;
	p2.rep->nodeTarget->succTarget->predTarget =
		rep->nodeTarget;
	// adjust sucessor targets.
	tempNode = rep->nodeTarget->succTarget;
	rep->nodeTarget->succTarget =
		p2.rep->nodeTarget->succTarget;
	p2.rep->nodeTarget->succTarget = tempNode;
} // transposeAfter

//-----------------------------------------------------------------------

template <class T>
Boolean CyclePosition1<T>::operator == (CyclePosition1& rhs)
{
	return (rep == rhs.rep);
}	// operator ==

//-----------------------------------------------------------------------

template <class T>
Boolean CyclePosition1<T>::operator != (CyclePosition1& rhs)
{
	return (rep != rhs.rep);
}	// operator !=

//-----------------------------------------------------------------------
/*
template <class T>
void CyclePosition1<T>::displayCyclePosition (
			preserves CyclePositionRecord*& p
		)
{
	printf ("%p\n\tRef Count:%ld   Pred:%p   Succ:%p   Node:%p\n",
		p, (long)p->refCount, p->predTarget, p->succTarget, p->nodeTarget);

	if (p->nodeTarget != NULL) {
		printf ("Node: %p\n\tlabel:%s   pred: %p   succ: %p\n\n",
			p->nodeTarget, (char *)p->nodeTarget->label,
			p->nodeTarget->predTarget, p->nodeTarget->succTarget);
	}	// end if
}	// displayCyclePosition

//-----------------------------------------------------------------------

template <class T>
void CyclePosition1<T>::displayRep (void)
{
	CyclePositionRecord* p;

	printf ("Position: ");
	displayCyclePosition (rep);

	p = rep->succTarget;
	while (p != rep) {
		displayCyclePosition (p);
      p = p->succTarget;
	}	// end while
}	// displayRep

*/
