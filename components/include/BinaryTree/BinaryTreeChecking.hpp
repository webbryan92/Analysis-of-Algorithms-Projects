#pragma once

/*
	Checking Version of BinaryTree
	Author: Dr. Holly
*/


template <
	template <class> class BinaryTree,
	class T
>
class BinaryTreeChecking1:
	public BinaryTree <T>
{
	typedef BinaryTree <T> BtOfT;
public:

//-------------------------------------------------------------------

void decompose (
		produces T& root,
		produces BinaryTreeChecking1& left,
		produces BinaryTreeChecking1& right
	)
{
	// assert that tree size > 0
	if (BtOfT::size () <= 0) {
		OutputDebugString ("Operation: Decompose\n");
		OutputDebugString ("Assertion failed: |t| > 0\n");
		DebugBreak ();
	}	// end if 

	BtOfT::decompose (root, left, right);
}	// decompose

//-------------------------------------------------------------------

T& operator [] (preserves Integer index)
{
	// assert that tree size > 0
	if (BtOfT::size () <= 0) {
		OutputDebugString ("Operation: Decompose\n");
		OutputDebugString ("Assertion failed: |t| > 0\n");
		DebugBreak ();
	}	// end if 

	return (BtOfT::operator [] (index));
}	// operator []
};



