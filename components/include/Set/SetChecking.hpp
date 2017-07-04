#pragma once

//
// checking version of Set 
// author: Dr. Holly
//

template <
	template <class, class> class Set,
	class T,
	class TCompare
>
class SetChecking1:
	public Set <T, TCompare>
{
	typedef Set <T, TCompare> SetInstance;
public:

//-------------------------------------------------------------------

void add (consumes T& x)
{
	// assert that s contains x
	if (SetInstance::contains(x)) {
		OutputDebugString ("Operation: add\n");
		OutputDebugString ("Assertion failed: self contains x\n");
		DebugBreak ();
	}	// end if 

	SetInstance::add (x);
}	// add

//-------------------------------------------------------------------

void remove (preserves T& xFromClient, produces T& xFromSet)
{
	// assert that s contains xFromClient
	if (!SetInstance::contains(xFromClient)) {
		OutputDebugString ("Operation: remove\n");
		OutputDebugString ("Assertion failed: self contains xFromClient\n");
		DebugBreak ();
	}	// end if 

	SetInstance::remove (xFromClient, xFromSet);
}	// remove

//-------------------------------------------------------------------

void removeAny (produces T& x)
{
	// assert |self| > 0
	if (SetInstance::size () <= 0) {
		OutputDebugString ("Operation: removeAny\n");
		OutputDebugString ("Assertion failed: |self| > 0\n");
		DebugBreak ();
	}	// end if 

	SetInstance::removeAny (x);
}	// removeAny
};
