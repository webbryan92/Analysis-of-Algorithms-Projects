#pragma once

/*
	Checking Version of SortingMachine
	Author: Dr. Holly
*/

template <
	template <class, class> class SortingMachine,	\
	class T,										\
	class TCompare
>
class SortingMachineChecking1:
	public SortingMachine <T, TCompare>
{
	typedef SortingMachine <T, TCompare> TSorter;
public:

//-------------------------------------------------------------------

void add (consumes T& x)
{
	// assert that sorting machine is in InsertionPhase
	if (!TSorter::isInInsertionMode()) {
		OutputDebugString("Operation: add\n");
		OutputDebugString("Assertion failed: isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	TSorter::add(x);
}	// add

//-------------------------------------------------------------------

void changeToExtractionMode (void)
{
	// assert that sorting machine is in InsertionPhase
	if (!TSorter::isInInsertionMode()) {
		OutputDebugString("Operation: changeToExtractionMode\n");
		OutputDebugString("Assertion failed: isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	TSorter::changeToExtractionMode();
}	// changeToExtractionMode


//-------------------------------------------------------------------

void removeFirst (produces T& x)
{
	// assert that sorting machine is not in InsertionPhase
	if (TSorter::isInInsertionMode()) {
		OutputDebugString("Operation: removeFirst\n");
		OutputDebugString("Assertion failed: !TSorter::isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	// assert that size of sorting machine > 0
	if (TSorter::size() <= 0) {
		OutputDebugString("Operation: removeFirst\n");
		OutputDebugString("Assertion failed: size() > 0\n");
		DebugBreak();
	}	// end if 

	TSorter::removeFirst(x);
}	// removeFirst
};



