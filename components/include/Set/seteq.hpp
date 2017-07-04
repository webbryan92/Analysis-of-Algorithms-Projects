#pragma once
/*
Equality Testing Capability for Set
Author: Dr. Holly
*/

template <class T, class SetOfT>
class SetEquality1:
	public SetOfT
{
public:
	Boolean operator == (preserves SetEquality1& rhs);
};


//------------------------------------------------------------------
// Exported Operations
//------------------------------------------------------------------


template <class T, class SetOfT>
Boolean SetEquality1<T, SetOfT>::operator == (
	preserves SetEquality1& rhs
	)
{
	Boolean equal;

	if (SetOfT::size() == rhs.size()) {
		SetOfT tempSet;
		equal = true;
		for (int i = 0, z = rhs.size(); i < z; i++) {
			T x;
			rhs.removeAny(x);
			equal = equal && SetOfT::contains(x);
			tempSet.add(x);
		} // end for
		tempSet.transferFrom(rhs);
	} // end if
	return (equal);
}	// operator ==

