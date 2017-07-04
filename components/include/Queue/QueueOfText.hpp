#pragma once
/*
	Realization of QueueOfText using raw nodes & pointers
	Author: Dr. Holly
*/


//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------


class QueueOfText
	//! is modeled by string(Text)
	//!   exemplar self
{
public: // standard Operations
	QueueOfText ();
		//! alters self
		//! ensures: self = < >
	~QueueOfText ();
	void clear (void);
		//! alters self
		//! ensures: self = < >
	void transferFrom (QueueOfText& source);
	//! alters self, source
	//! ensures self = #source  and  source = < >
	QueueOfText& operator = (QueueOfText& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// QueueOfText Specific Operations
	void enqueue (Text& x);
		//! alters self
		//! consumes x
		//! ensures: self = #self * <#x>
	void dequeue (Text& x);
		//! alters self
		//! produces x
		//! requires: self /= < >
		//! ensures: <x> is prefix of #self  and  
		//!          self = #self[1,|#self|)
	void replaceFront (Text& x);
		//! alters self, x
		//! requires: self /= < >
		//!  ensures: x is prefix of #self and
		//!           self = <#x> * #self[1,|#self|)
	Text& front (void);
		//! preserves self
		//! requires: self /= < >
		//!  ensures: <front> is prefix of self
	Integer length (void);
		//! preserves self
		//! ensures: length = |self|

	friend ostream & operator<< (ostream &os, QueueOfText& q);
	//! alters os
	//! preserves q

private: // representation

	class NodeRecord {
	public:
		Text value;
		NodeRecord* next;
	};

	NodeRecord* head;

private: // local Operations
	Integer countNodes (NodeRecord* p);
	void copyNodes (NodeRecord*& toHead, NodeRecord* fromHead);
	void reclaimAllNodes (NodeRecord*& p);
	void displayRep (ostream &os);

private: // disallowed QueueOfText Operations
	QueueOfText (const QueueOfText& s);
	QueueOfText* operator & (void) {return (this);};
	const QueueOfText* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------


Integer QueueOfText::countNodes (NodeRecord* p)
	// ensures: countNodes = number of nodes in linked list starting with node located at address p;
{
	if (p != NULL) {
		return countNodes(p->next) + 1;
	} else {
		return 0;
	} // end if
}	// countNodes

//-----------------------------------------------------------------------


void QueueOfText::copyNodes (NodeRecord*& toP, NodeRecord* fromP)
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


void QueueOfText::reclaimAllNodes (NodeRecord*& p)
	// ensures: p = NULL;
{
	if (p != NULL) {
		reclaimAllNodes(p->next);
		delete (p);
	} // end if
}	// reclaimAllNodes

//-----------------------------------------------------------------------


void QueueOfText::displayRep (ostream &os)
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

QueueOfText::QueueOfText ()
{
	head = NULL;
}	// QueueOfText

//-----------------------------------------------------------------------

QueueOfText::~QueueOfText ()
{
	reclaimAllNodes(head);
}	// ~QueueOfText

//-----------------------------------------------------------------------

void QueueOfText::transferFrom(QueueOfText& source)
{
	reclaimAllNodes(head);
	head = source.head;
	source.head = NULL;
}

//-----------------------------------------------------------------------

QueueOfText& QueueOfText::operator = (QueueOfText& rhs)
{
	reclaimAllNodes(head);
	copyNodes(head, rhs.head);
	return (*this);
} // operator =

//-----------------------------------------------------------------------


void QueueOfText::clear (void)
{
	reclaimAllNodes(head);
}	// clear

//-----------------------------------------------------------------------

void QueueOfText::enqueue (Text& item)
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

void QueueOfText::dequeue (Text& item)
{
	NodeRecord* existingNode;

	existingNode = head;
	item.transferFrom(existingNode->value);
	head = existingNode->next;
	delete (existingNode);
}	// dequeue

//-----------------------------------------------------------------------

void QueueOfText::replaceFront(Text& x)
{
	Text temp;

	temp.transferFrom(head->value);
	head->value.transferFrom(x);
	x.transferFrom(temp);
}	// replaceFront

//-----------------------------------------------------------------------

Text& QueueOfText::front ()
{
	return (head->value);
}  // front

//-----------------------------------------------------------------------

Integer QueueOfText::length (void)
{
	return (countNodes(head));
}	// length

//-----------------------------------------------------------------------


ostream & operator<<(ostream &os, QueueOfText& q)
{
	QueueOfText temp;

	os << "<";

	for (int i = 0, z = q.length(), lastItem = z - 1; i < z; i++) {
		Text x;

		q.dequeue(x);
		os << x;
		temp.enqueue(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	} // end for
	os << ">";
	q.transferFrom(temp);
	return (os);
}

