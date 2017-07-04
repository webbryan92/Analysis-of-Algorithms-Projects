/*
Implementation of wrapper for the scalar type char
Author:	Dr. Holly
*/

#include "wrapper.h"

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

std::ostream& operator << (
			alters std::ostream& s,
			preserves Character& x
		)
{
	s << x.c;
	return (s);
} // operator <<

//-------------------------------------------------------------------------

std::istream& operator >> (
         alters std::istream& s,
         alters Character& x
      )
{
	char input_line[100];

	std::cin.getline (input_line, 99);
	x.c = input_line[0];
	return (s);
}  // operator >>
