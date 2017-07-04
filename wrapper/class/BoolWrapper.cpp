/*
Implementation of scalar type Boolean
Author: Dr. Holly
*/

#include "wrapper.h"

std::ostream& operator << (
         alters std::ostream& s,
         preserves Boolean& x
      )
{
	if (x) {
		s << "true";
	} else {
		s << "false";
	}	// end if
   return (s);
}  // operator <<

//-------------------------------------------------------------------------

std::istream& operator >> (
         alters std::istream& s,
         alters Boolean& x
      )
{
	char inputLine[100];

	std::cin.getline (inputLine, 99);
	if	(
			(strcmp (inputLine, "0") == 0) ||
			(_stricmp (inputLine, "false")))
	{
		x = false;
	} else {
		x = true;
	}	// end if
	return (s);
}  // operator >>
