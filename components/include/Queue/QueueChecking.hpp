#pragma once
/*
	Checking Version of Queue
	Author: Dr. Holly
*/

template <
	template <class> class Queue,
	class T
>
class QueueChecking1:
	public Queue <T>
{
	typedef Queue <T> QueueOfT;
public:

//-------------------------------------------------------------------

void dequeue (T& x)
{
	// assert that length > 0
	if (QueueOfT::length() <= 0) {
		OutputDebugString ("Operation: dequeue\n");
		OutputDebugString ("Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	QueueOfT::dequeue (x);
}	// dequeue

//-------------------------------------------------------------------

T& front(void)
{
	// assert that length > 0
	if (QueueOfT::length () <= 0) {
		OutputDebugString ("Operation: front\n");
		OutputDebugString ("Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	return (QueueOfT::front());
}	// front

//-------------------------------------------------------------------

void replaceFront(T& x)
{
	// assert that length > 0
	if (QueueOfT::length () <= 0) {
		OutputDebugString ("Operation: replaceFront\n");
		OutputDebugString ("Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	QueueOfT::replaceFront(x);
}	// replaceFront
};

