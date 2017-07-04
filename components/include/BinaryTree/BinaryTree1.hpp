#pragma once

/*
	Realization of BinaryTree using 2WayDagPosition
	Author: Dr. Holly
*/

#include "DAGPosition\DAGPosition1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
	//! Binary_Tree is modeled by tuple of
	//!      x: T
	//!      left_subtree: Binary_Tree
	//!      right_subtree: Binary_Tree
	//! exemplar self
class BinaryTree1
{
public: // standard Operations
	BinaryTree1 ();
		//! alters self
		//! ensures: self = EMPTY
	~BinaryTree1 ();
	void clear (void);
		//! alters self
		//! ensures: self = EMPTY
	void transferFrom(BinaryTree1& source);
	//! alters self, source
	//! ensures self = #source  and  source = EMPTY
	BinaryTree1& operator = (BinaryTree1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// BinaryTree1 Specific Operations
	void compose (T& x, BinaryTree1& left, BinaryTree1& right);
		//! produces self
		//! consumes x, left, right
		//! ensures: self = (x, left, right)
	void decompose (T& x, BinaryTree1& left, BinaryTree1& right);
		//! consumes self
		//! produces x, left, right
		//! requires: self /= EMPTY
		//! ensures: #self = (x, left, right)
	T& label (void);
		//! consumes self
		//! produces x, left, right
		//! requires: self /= EMPTY
		//! ensures: #self = (x, left, right)
	Integer size (void);
		//! preserves self
		//! ensures: size = |self|
	Integer height (void);
		//! preserves self
		//! ensures: height = height of self

	
	friend ostream & operator<< <T>(ostream &os, BinaryTree1& x);
	//! alters os
	//! preserves x

private: // representation
	enum {leftSubtree = 0, rightSubtree = 1};

	// create BinaryTree's label
	class TreeLabelRecord {
	public:
		T item;
		Integer size;
		Integer height;

		void transferFrom(TreeLabelRecord& source) {
			item.transferFrom(source.item);
			size.transferFrom(source.size);
			height.transferFrom(source.height);
		} // transferFrom

		friend ostream & operator<< <T>(ostream &os, TreeLabelRecord& r) {
			os << "(" << r.item << "," << r.size << "," << r.height << ")";
			return os;
		} // operator <<
	};

	typedef DagPosition1 <TreeLabelRecord, 2> TwoWayDagPosition;
	TwoWayDagPosition node;

private: // local Operations
	inline Integer treeSize (void);
	inline Integer treeHeight (void);
	void copy (TwoWayDagPosition& from, TwoWayDagPosition& to);
	void displayRepInOrder (ostream &os, TwoWayDagPosition& root);

private: // disallowed BinaryTree1 Operations

	BinaryTree1 (const BinaryTree1& s);
	BinaryTree1* operator & (void) {return (this);};
	const BinaryTree1* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

template <class T>
inline Integer BinaryTree1<T>::treeSize (void)
{
	return (node.label().size);
}   // treeSize

//-----------------------------------------------------------------------

template <class T>
inline Integer BinaryTree1<T>::treeHeight (void)
{
   return (node.label().height);
}   // treeHeight

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::copy (
		TwoWayDagPosition& from,
		TwoWayDagPosition& to
	)
	// pre: to.label() = {T.initialized, 0, 0}
{
	if (!from.isZero()) {
		TreeLabelRecord label;
		TwoWayDagPosition left, right, leftCopy, rightCopy;

		from.swapWithTarget(leftSubtree, left);
		from.swapWithTarget(rightSubtree, right);
		copy(left, leftCopy);
		copy(right, rightCopy);
		from.swapWithTarget(leftSubtree, left);
		from.swapWithTarget(rightSubtree, right);

		label = from.label();
		to.labelNew(label);
		to.swapWithTarget(leftSubtree, leftCopy);
		to.swapWithTarget(rightSubtree, rightCopy);
	} // end if
} // copy

//------------------------------------------------------------

template <class T>
void BinaryTree1<T>::displayRepInOrder (ostream &os, TwoWayDagPosition& root)
{
	if (!root.isZero()) {
		Integer height = root.label().height;
		TwoWayDagPosition left = root;
		left.applyTarget(leftSubtree);
		displayRepInOrder(os, left);
		os << " H:" << right << setw(2) << height;
		os << setw(height) << " ";
		os << root.label() << endl;
		TwoWayDagPosition right = root;
		right.applyTarget(rightSubtree);
		displayRepInOrder(os, right);
	} // end if
}	// displayRepInOrder

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
BinaryTree1<T>::BinaryTree1 ()
{
}   // BinaryTree1

//-----------------------------------------------------------------------

template <class T>
BinaryTree1<T>::~BinaryTree1 ()
{
}   // ~BinaryTree1

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::transferFrom(BinaryTree1& source)
{
	node.transferFrom(source.node);
}   // transferFrom

//-----------------------------------------------------------------------

template <class T>
BinaryTree1<T>& BinaryTree1<T>::operator = (BinaryTree1& rhs)
{
	node.clear();
	copy(rhs.node, node);
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::clear (void)
{
   node.clear();
}   // clear

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::compose (
         T& x,
         BinaryTree1& left,
         BinaryTree1& right
      )
{
   TreeLabelRecord label;
   Integer leftHeight, rightHeight;

   label.item.transferFrom(x);
   leftHeight = left.treeHeight();
   rightHeight = right.treeHeight();
   label.height =
      ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
   label.size = left.treeSize() + right.treeSize() + 1;
   node.labelNew(label);

   node.swapWithTarget(leftSubtree, left.node);
   node.swapWithTarget(rightSubtree, right.node);
}   // compose

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::decompose (
         T& x,
         BinaryTree1& left,
         BinaryTree1& right
      )
{
   TreeLabelRecord label;

   node.replaceLabel(label);
   x.transferFrom(label.item);
   node.swapWithTarget(leftSubtree, left.node);
   node.swapWithTarget(rightSubtree, right.node);
   node.clear();
}   // decompose

//-----------------------------------------------------------------------

template <class T>
T& BinaryTree1<T>::label (void)
{
   return (node.label().item);
}  // label

//-----------------------------------------------------------------------

template <class T>
Integer BinaryTree1<T>::size (void)
{
   return (self.treeSize());
}   // size

//-----------------------------------------------------------------------

template <class T>
Integer BinaryTree1<T>::height (void)
{
   return (self.treeHeight());
}   // height

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, BinaryTree1<T>& root)
{
	root.displayRepInOrder(os, root.node);
	return (os);
} // operator<<
