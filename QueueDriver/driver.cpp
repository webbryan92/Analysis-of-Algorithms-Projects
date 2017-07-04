//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "Queue\Queue1.hpp"


#ifdef NDEBUG
// When NDEBUG is defined, that means: 
//   Compiling in Release Configuration = Not Debug configuration
typedef Queue1<Text> QueueOfText;
#else
// Compiling in Debug configuration
#include "Queue\QueueChecking.hpp"
typedef QueueChecking1 <Queue1, Text> QueueOfText;
#endif

//-------------------------------------------------------------------
// program constants
//-------------------------------------------------------------------

void displayMenu(void)
//! ensures: a menu of commands to all user to manipulate a queue is displayed to the user
{
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;
	cout << "     Command -  Result" << endl;
	cout << "        g - toggle display menu" << endl;
	cout << "        e - enqueue" << endl;
	cout << "        d - dequeue" << endl;
	cout << "        r - replaceFront" << endl;
	cout << "        f - front" << endl;
	cout << "        z - length" << endl;
	cout << "        x - transferFrom" << endl;
	cout << "        = - copy" << endl;
	cout << "        l - load from file" << endl;
	cout << "        o - output to file" << endl;
	cout << "        p - display" << endl;
	cout << "        c - clear" << endl;
	cout << "        q - quit program" << endl;
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl << "        command:";
}	// showMenu

	//-------------------------------------------------------------------

void getCommand(Character& command)
//! ensures: getCommand = a keyboard character entered by the user
{
	cin >> command;
	cout << endl;
}	// getCommand

	//-------------------------------------------------------------------

Integer getIndex(void)
//! ensures: getIndex = 1 or getIndex = 2 
{
	Integer index;

	do {
		cout << "which Queue? 1 or 2:";
		cin >> index;
	} while ((index < 1) || (index > 2));
	cout << endl;
	return (index);
}	// getIndex

	//-------------------------------------------------------------------

void getText(Text& s)
//! ensures: there exists x:String(Character)
//!          (s = x and 0 <= |x| and
//!           x contains keyboard characters typed by user) 
{
	cout << "Enter text string:";
	cin >> s;
}	// getText

	//-------------------------------------------------------------------

void doEnqueue(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          allows user to enter a Text string x (from the keyboard)  and
//!          adds the Text string x to the end of chosen queue  and
//!          provides feedback to the user about what was done
{
	Integer index;
	Text x;

	cout << "Enqueue onto ";
	index = getIndex();
	getText(x);
	if (index == 1) {
		q1.enqueue(x);
	}
	else {
		q2.enqueue(x);
	}	// end if
	cout << endl << "q" << index << ".enqueue(x); executed." << endl;
	cout << "x = " << x << endl;
}	// doEnqueue

	//-------------------------------------------------------------------

void doDequeue(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          if the queue chosen by the user contains at least 1 item then
//!            doDequeue removes the Text string x the front of the chosen queue   and
//!          provides feedback to the user about what was done
{
	Integer index, z;
	Text x;

	cout << "Dequeue from ";
	index = getIndex();
	if (index == 1) {
		z = q1.length();
		if (z > 0) {
			q1.dequeue(x);
		} // end if
	}
	else {
		z = q2.length();
		if (z > 0) {
			q2.dequeue(x);
		} // end if
	}	// end if
	if (z > 0) {
		cout << endl << "q" << index << ".dequeue(x); executed." << endl;
		cout << "x = " << x << endl;
	}
	else {
		cout << "Error: |q" << index << "| = 0 - cannot dequeue from an empty queue." << endl;
	} // end if
}	// doDequeue

	//-------------------------------------------------------------------

void doReplaceFront(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          if the queue chosen by the user contains at least 1 item then
//!            allows user to enter a Text string x (from the keyboard)  and
//!            then doReplaceFront replaces the front of the chosen queue with x   and
//!          provides feedback to the user about what was done
{
	Integer index, z;
	Text x;

	cout << "Replace front of ";
	index = getIndex();
	if (index == 1) {
		z = q1.length();
		if (z > 0) {
			getText(x);
			q1.replaceFront(x);
		} // end if
	}
	else {
		z = q2.length();
		if (z > 0) {
			getText(x);
			q2.replaceFront(x);
		} // end if
	}	// end if
	if (z > 0) {
		cout << endl << "q" << index << ".replaceFront(x); executed." << endl;
		cout << "x = " << x << endl;
	}
	else {
		cout << "Error: |q" << index << "| = 0 - cannot replaceFront on an empty queue." << endl;
	} // end if
}	// doReplaceFront

	//-------------------------------------------------------------------

void doFront(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          if the queue chosen by the user contains at least 1 item then
//!            displays the item at the front of the chosen queue   and
//!          provides feedback to the user about what was done
{
	Integer index;

	cout << "Access front of ";
	index = getIndex();
	if (index == 1) {
		if (q1.length() > 0) {
			cout << "q1.front() = " << q1.front() << endl;
		}
		else {
			cout << "Error: |q1| = 0 - cannot access front of an empty queue." << endl;
		} // end if
	}
	else {
		if (q2.length() > 0) {
			cout << "q2.front() = " << q2.front() << endl;
		}
		else {
			cout << "Error: |q2| = 0 - cannot access front of an empty queue." << endl;
		} // end if
	}	// end if
}	// doFront

	//-------------------------------------------------------------------

void doLength(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          provides feedback to the user about length of the chosen queue
{
	Integer index, z;

	cout << "Length of ";
	index = getIndex();
	if (index == 1) {
		z = q1.length();
	}
	else {
		z = q2.length();
	}	// end if
	cout << "|q" << index << "| = " << z << endl;
}	// doLength

	//-------------------------------------------------------------------

void doClear(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          clears the contents of the chosen queue   and
//!          provides feedback to the user about what was done

//! ensures: allows user to clear the contents of q1 or q2
{
	Integer index;

	cout << "Clear ";
	index = getIndex();
	if (index == 1) {
		q1.clear();
	}
	else {
		q2.clear();
	}	// end if
	cout << endl << "q" << index << ".clear(); executed." << endl;
}	// doClear

	//-------------------------------------------------------------------

void doTransferFrom(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          transfers the chosen queue to the other queue   and
//!          provides feedback to the user about what was done
{
	Integer index;

	cout << "Transfer from ";
	index = getIndex();
	if (index == 1) {
		q2.transferFrom(q1);
		cout << endl << "q2.transferFrom(q1); executed." << endl;
	}
	else {
		q1.transferFrom(q2);
		cout << endl << "q1.transferFrom(q2); executed." << endl;
	} // end if
}	// doTransferFrom

	//-------------------------------------------------------------------

void doCopy(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          copies the chosen queue to the other queue   and
//!          provides feedback to the user about what was done
{
	cout << "Copy ";
	if (getIndex() == 1) {
		q2 = q1;
		cout << "q2 = q1; executed." << endl;
	}
	else {
		q1 = q2;
		cout << "q1 = q2; executed." << endl;
	}	// end if
}	// doCopy

	//-------------------------------------------------------------------

void display(QueueOfText& q)
//! ensures: q = #q and displays the contents of q
{
	QueueOfText qTemp;

	cout << "<";
	for (int i = 0, z = q.length(), lastItem = (z - 1); i < z; i++) {
		Text x;

		q.dequeue(x);
		cout << x;
		qTemp.enqueue(x);
		if (i < lastItem) {
			cout << ",";
		} // end if
	}	// end for
	cout << ">" << endl;
	q.transferFrom(qTemp);
}	// display

	//-------------------------------------------------------------------

void doDisplay(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          calls display which then displays the value of the chosen queue
{
	Integer index;

	cout << "Display ";
	index = getIndex();
	cout << "q" << index << " = ";
	if (index == 1) {
		display(q1);
	}
	else {
		display(q2);
	}	// end if
}	// doDisplay

	//-------------------------------------------------------------------

void doInputFromFile(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows the user to enter a data filename  and
//!          if the data file exists then loads the Text data from that file then
//!            allows user to choose which queue to work with, either q1 or q2  then
//!            transfers the loaded data to the chosen queue   and
//!          provides feedback to the user about what was done

//! ensures: allows user load Text string data from a data file into either q1 or q2
{
	Boolean successful;
	Integer size, index;
	Text filename, x;
	File input;
	QueueOfText q;

	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;

	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	}
	else {
		input.read(size, successful);
		for (int i = 0; i < size; i++) {
			input.read(x, successful);
			q.enqueue(x);
		}	// end for
		input.closeFile(successful);

		cout << "Load file into ";
		index = getIndex();
		if (index == 1) {
			q1.transferFrom(q);
		}
		else {
			q2.transferFrom(q);
		}	// end if
	}	// end if
}	// doInputFromFile

	//-------------------------------------------------------------------

void doOutputToFile(QueueOfText& q1, QueueOfText& q2)
//! ensures: allows user to choose to work with either q1 or q2  and
//!          allows the user to enter a data filename  and
//!          the contents of the chosen queue is written to the file  and
//!          the chosen queue's value is preserved
{
	Boolean successful;
	Integer z, index;
	Text filename, x;
	File output;
	QueueOfText q;

	// get file name from user
	// open file for writing
	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;
	output.openFile(filename, File::openForWrite, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	}
	else {
		// find out from which Queue to output contents.
		cout << "Output from ";
		index = getIndex();

		// transfer contents of chosen Queue into local q.
		if (index == 1) {
			q.transferFrom(q1);
		}
		else {
			q.transferFrom(q2);
		}	// end if

			// write to file:
			// 1) write an Integer telling how many items are in q
			// 2) write each item found in q
			// note: 
			// after loop has finished, q must contain
			// the same values as before, in same order.
		z = q.length();
		output.write(z, successful);
		for (int i = 0; i < z; i++) {
			q.dequeue(x);
			output.write(x, successful);
			q.enqueue(x);
		}	// end for
		output.closeFile(successful);

		// transfer the contents of local q back into original
		if (index == 1) {
			q1.transferFrom(q);
		}
		else {
			q2.transferFrom(q);
		}	// end if
	}  // end if
}	// doOutputToFile

	//-------------------------------------------------------------------

void dispatchCommand(
	Character command,
	Boolean& showMenu,
	QueueOfText& q1,
	QueueOfText& q2
	)
	//! ensures: a "do" command is called that corresponds to the character found in command
{
	switch (command) {
	case 'g':	// toggle display Menu
		showMenu = !showMenu;
		break;
	case 'e':
		doEnqueue(q1, q2);
		break;
	case 'd':
		doDequeue(q1, q2);
		break;
	case 'r':
		doReplaceFront(q1, q2);
		break;
	case 'f':
		doFront(q1, q2);
		break;
	case 'z':
		doLength(q1, q2);
		break;
	case 'x':
		doTransferFrom(q1, q2);
		break;
	case '=':
		doCopy(q1, q2);
		break;
	case 'l':
		doInputFromFile(q1, q2);
		break;
	case 'o':
		doOutputToFile(q1, q2);
		break;
	case 'p':
		doDisplay(q1, q2);
		break;
	case 'c':
		doClear(q1, q2);
		break;
	case 'q':
		cout << "Quit Command Interpreter" << endl;
		break;
	default:
		cout << "Unknown command: " << command << endl;
		cout << "Please reenter your command" << endl;
		break;
	}	// end switch
}	// dispatchCommand

	//-------------------------------------------------------------------

void commandController(
	QueueOfText& q1,
	QueueOfText& q2,
	Boolean& showMenu
	)
	//! ensures: the command interpreter main loop continues to execute while 'q' has not been entered
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, q1, q2);
	} while (command != 'q' && command != 'Q');
} // commandController

  //-------------------------------------------------------------------
  // main executable body
  //-------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	QueueOfText q1, q2;

	commandController(q1, q2, showMenu);
	cout << "end program" << endl;
	return 0;
}	// end main
