/*
Implementation of wrapper for the scalar type int
Author: Dr. Holly
*/

#include "wrapper.h"

std::istream& operator >> (
         alters std::istream& s,
         alters Integer& x
      )
{
	char input_line[100];
	int value;

	std::cin.getline (input_line, 99);
	sscanf (input_line, "%d", &value);
	x = value;
	return (s);
}  // operator >>

