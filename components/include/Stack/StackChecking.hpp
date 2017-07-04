#pragma once

/*
	Checking Version of Stack
	Author: Dr. Holly
*/

template <
	template <class> class Stack,	\
	class T
>
class StackChecking1:
	public Stack <T>
{
	typedef Stack <T> StackOfT;
public:
void pop (T& x)
{
	// assert that length is > 0
	if (StackOfT::length () <= 0) {
		OutputDebugString ("Operation: pop\n");
		OutputDebugString ("Assertion failed: |s| > 0\n");
		DebugBreak ();
	}	// end if 

	StackOfT::pop (x);
}	// pop

//-------------------------------------------------------------------

void replaceTop (T& x)
{
	// assert that length is > 0
	if (StackOfT::length () <= 0) {
		OutputDebugString ("Operation: replaceTop\n");
		OutputDebugString ("Assertion failed: |s| > 0\n");
		DebugBreak ();
	}	// end if 

	StackOfT::replaceTop (x);
}	// replaceTop

//-------------------------------------------------------------------

T& top (void)
{
	// assert that length > 0
	if (StackOfT::length () <= 0) {
		OutputDebugString ("Operation: top\n");
		OutputDebugString ("Assertion failed: |s| > 0\n");
		DebugBreak ();
	}	// end if 

	return (StackOfT::top());
}	// top
};

