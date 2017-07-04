#include "wrapper.h"


#include "C455-IntegerSorter1.hpp"
#include "C455-IntegerSorter1V2.hpp"
#include "C455-IntegerSorter2.hpp"
#include "C455-IntegerSorter3.hpp"
#include "C455-IntegerSorter4.hpp"
#include "C455-IntegerSorter5.hpp"

enum { sorter1 = 1, sorter2 = 2, sorter3 = 3, sorter4 = 4, sorter5 = 5, sorter6 = 6};

//---------------------------------------------------------------------------

template <class IntegerSorter>
void loadRandom(IntegerSorter& s, Integer size)
// requires: size >= 0
{
	s.setMaxSize(size);
	for (int i = 0; i < size; i++) {
		Integer value = rand() % INT_MAX;
		s.add(value);
	} // end for
} // loadRandom
template <class IntegerSorter>
void loadSorted(IntegerSorter& s, Integer size)
// requires: size >= 0
{
	s.setMaxSize(size);
	for (int i = size; i > 0; i--) {
		Integer value = i;
		s.add(value);
	} // end for
} // loadSorted

   //---------------------------------------------------------------------------

template <class IntegerSorter>
void displayItems(IntegerSorter& s)
{
	Integer x;
	for (int i = 0, z = s.size(); i < z; i++) {
		s.removeFirst(x);
		cout << x << endl;
	} // end for
} // displayItems

  //---------------------------------------------------------------------------

void main(int argc, char* argv[])
{
	// Command line arguments:
	// #1) Supply as the 1st argument either 1, 2, or 3: a 1 to run IntegerSorter1, a 2 for IntegerSorter2, etc.
	// #2) Supply an integer as the 2nd argument to specify how many integers are to be sorted, e.g., 10000 
	// #3) Optional, but if you supply anything as a 3rd command line argument, then the sorted items will be displayed

	// In Visual Studio set the command arguments in the Project Properties by navigating to:
	// Configuration Properties | Debugging | Command Arguments

	// Example command line arguments: 1 10000 yes

	Boolean displaySortedItems = (argc == 4);
	Integer collectionSize, whichSorter;

	if (argc > 2) {
		// Command line arguments were supplied, use them
		sscanf(argv[1], "%d", (int *)&whichSorter);
		sscanf(argv[2], "%d", (int *)&collectionSize);
		if (collectionSize < 0) {
			collectionSize = 1000;
		} // end if
	}
	else {
		// Set default values when command line arguments are not supplied
		whichSorter = 1;
		collectionSize = 1000;
	} // end if


	cout << "Sorting beginning on " << collectionSize << " items." << endl;

	switch (whichSorter) {
	case sorter1:
	{
		IntegerSorter1 s1;
		cout << "Sorting using IntegerSorter1" << endl;
		loadRandom(s1, collectionSize);
		s1.changeToExtractionMode();
		if (displaySortedItems) {
			displayItems(s1);
		} // end if
	}
	break;
	case sorter2:
	{
		IntegerSorter2 s2;
		cout << "Sorting using IntegerSorter2" << endl;
		loadRandom(s2, collectionSize);
		//loadReverseSorted(s2, collectionSize);
		s2.changeToExtractionMode();
		if (displaySortedItems) {
			displayItems(s2);
		} // end if
	}
	break;
	case sorter3:
	{
		IntegerSorter3 s3;
		cout << "Sorting using IntegerSorter3" << endl;
		loadRandom(s3, collectionSize);
		s3.changeToExtractionMode();
		if (displaySortedItems) {
			displayItems(s3);
		} // end if
	}
	break;
	case sorter4:
	{
		IntegerSorter1V2 s4;
		cout << "Sorting using IntegerSorter4" << endl;
		loadRandom(s4, collectionSize);
		s4.changeToExtractionMode();
		if (displaySortedItems) {
			displayItems(s4);
		} // end if
	}
	break;
	case sorter5:
	{
		IntegerSorter4 s5;
		cout << "Sorting using IntegerSorter5" << endl;
		loadRandom(s5, collectionSize);
		//loadSorted(s5, collectionSize);
		s5.changeToExtractionMode();
		if (displaySortedItems) {
			displayItems(s5);
		} // end if
	}
	break;
	case sorter6:
	{
		IntegerSorter5 s6;
		cout << "Sorting using IntegerSorter6" << endl;
		//loadRandom(s6, collectionSize);
		loadSorted(s6, collectionSize);
		s6.changeToExtractionMode();
		if (displaySortedItems) {
			displayItems(s6);
		} // end if
	}
	break;
	default:
		break;
	} // end switch


	cout << "Finished sorting" << endl;

	system("pause");
}