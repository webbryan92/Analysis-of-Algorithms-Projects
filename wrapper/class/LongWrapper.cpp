/*
Implementation of wrapper for the scalar type long int
Author: Dr. Holly
*/

#include "wrapper.h"

std::istream& operator >> (
         alters std::istream& s,
         alters LongInteger& x
      )
{
	char input_line[100];
	long int value;

	std::cin.getline (input_line, 99);
	sscanf (input_line, "%ld", &value);
	x = value;
	return (s);
}  // operator >>
