#pragma once
/*
	Realization of Queue using raw nodes & pointers
	Author: Dr. Holly
*/


//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class Queue0
	//! is modeled by string(T)
	//!   exemplar self
{
public: // standard Operations
	Queue0 ();
		//! alters self
		//! ensures: self = < >
	~Queue0 ();
	void clear (void);
		//! alters self
		//! ensures: self = < >
	void transferFrom (Queue0& source);
	//! alters self, source
	//! ensures self = #source  and  source = < >
	Queue0& operator = (Queue0& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// Queue0 Specific Operations
	void enqueue (T& item);
		//! alters self
		//! consumes item
		//! ensures: self = #self + <#item>
	void dequeue (T& item);
		//! alters self
		//! produces item
		//! requires: self /= < >
		//! ensures: <x> is prefix of #self  and  
		//!          self = #self[1,|#self|)
	void replaceFront (T& x);
		//! alters self, x
		//! requires: self /= < >
		//!  ensures: x is prefix of #self and
		//!           self = <#x> * #self[1,|#self|)
	T& front (void);
		//! preserves self
		//! requires: self /= < >
		//!  ensures: <front> is prefix of self
	Integer length (void);
		//! preserves self
		//! ensures: length = |self|

	friend ostream & operator<< <T>(ostream &os, Queue0<T>& q);
	//! alters os
	//! preserves q

private: // representation

	class NodeRecord {
	public:
		T value;
		NodeRecord* next;
	};

	NodeRecord* head;

private: // local Operations
	Integer countNodes (NodeRecord* p);
	void copyNodes (NodeRecord*& toHead, NodeRecord* fromHead);
	void reclaimAllNodes (NodeRecord*& p);
	void displayRep (ostream &os);

private: // disallowed Queue0 Operations
	Queue0 (const Queue0& s);
	Queue0* operator & (void) {return (this);};
	const Queue0* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

template <class T>
Integer Queue0<T>::countNodes (NodeRecord* p)
	// ensures: countNodes = number of nodes in linked list starting with node located at address p;
{
	if (p != NULL) {
		return countNodes(p->next) + 1;
	} else {
		return 0;
	} // end if
}	// countNodes

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::copyNodes (NodeRecord*& toP, NodeRecord* fromP)
{
	if (fromP == NULL) {
		toP = NULL;
	} else {
		toP = new NodeRecord;

		toP->value = fromP->value;
		copyNodes(toP->next, fromP->next);
	} // end if
} // copyNodes

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::reclaimAllNodes (NodeRecord*& p)
	// ensures: p = NULL;
{
	if (p != NULL) {
		reclaimAllNodes(p->next);
		delete (p);
	} // end if
}	// reclaimAllNodes

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::displayRep (ostream &os)
{
	NodeRecord* p;
	Integer c;

	os << "&head: " << &head << endl;
	os << " head: " <<  head << endl;
	c = 1;
	p = head;
	while (p != NULL) {
		os << " Node: #" << c;
		os << " Address: " << p;
		os << "\t(" << p->value;
		os << ", " << p->next << ")" << endl;
		p = p->next;
		c++;
	}	// end while
}	// displayRep

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
Queue0<T>::Queue0 ()
{
	head = NULL;
}	// Queue0

//-----------------------------------------------------------------------

template <class T>
Queue0<T>::~Queue0 ()
{
	reclaimAllNodes(head);
}	// ~Queue0

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::transferFrom(Queue0& source)
{
	reclaimAllNodes(head);
	head = source.head;
	source.head = NULL;
}

//-----------------------------------------------------------------------

template <class T>
Queue0<T>& Queue0<T>::operator = (Queue0& rhs)
{
	reclaimAllNodes(head);
	copyNodes(head, rhs.head);
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::clear (void)
{
	reclaimAllNodes(head);
	head = NULL;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::enqueue (T& item)
{
	NodeRecord* newNode = new NodeRecord;

	newNode->value.transferFrom(item);
	newNode->next = NULL;

	if (head == NULL) {
		head = newNode;
	} else {
		NodeRecord* p;

		p = head;
		while (p->next != NULL) {
			p = p->next;
		}	// end while
		p->next = newNode;
	} // end if
}	// enqueue

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::dequeue (T& item)
{
	NodeRecord* existingNode;

	existingNode = head;
	item.transferFrom(existingNode->value);
	head = existingNode->next;
	delete (existingNode);
}	// dequeue

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::replaceFront(T& x)
{
	T temp;

	temp.transferFrom(head->value);
	head->value.transferFrom(x);
	x.transferFrom(temp);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T>
T& Queue0<T>::front ()
{
	return (head->value);
}  // front

//-----------------------------------------------------------------------

template <class T>
Integer Queue0<T>::length (void)
{
	return (countNodes(head));
}	// length

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, Queue0<T>& q)
{
#ifdef NDEBUG
	Queue0<T> temp;

	os << "<";

	for (int i = 0, z = q.length(), lastItem = z - 1; i < z; i++) {
		T x;

		q.dequeue(x);
		os << x;
		temp.enqueue(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	} // end for
	os << ">";
	q.transferFrom(temp);
#else
	q.displayRep(os);
#endif
	return (os);
}

