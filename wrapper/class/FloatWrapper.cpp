/*
Implementation of wrapper for float
Author: Dr. Holly
*/

#include "wrapper.h"


std::istream& operator >> (
         alters std::istream& s,
         alters Float& x
      )
{
	char input_line[100];
	float value;

	std::cin.getline (input_line, 99);
	sscanf (input_line, "%f", &value);
	x = value;
	return (s);
}  // operator >>
