#pragma once
#include "Wrapper.h"

class Rect: public RECT
{
	// Inherits the representation from Window's RECT
	// RECT's representation is: int left, top, right, bottom

	// Adds the following operations: constructor, clear, operator =, transferFrom, operator <<
	// Use Rect where ever a Windows program calls for a RECT

private:
	void initializeRep()
		// ensures: self = (0, 0, 0, 0)
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;	
	} // initializeRep

	void copyRep (Rect& from)
		// ensures: self = from
	{
		left = from.left;
		top = from.top;
		right = from.right;
		bottom = from.bottom;	
	} // copyRep

public:
	Rect()
		// ensures: self = (0, 0, 0, 0)
	{
		initializeRep();
	} // Rect()

	void clear(void)
		// ensures: self = (0, 0, 0, 0)
	{
		initializeRep();	
	} // clear

	Rect& operator = (Rect& rhs)
		// ensures: self = rhs
	{
		copyRep(rhs);	
		return (*this);
	} // operator =

	void transferFrom(Rect& source)
		// ensures: self = source and source = (0, 0, 0, 0)
	{
		copyRep(source);	
		source.initializeRep();
	} // transferFrom

	friend ostream& operator << (ostream &os, Rect& r)
	{
		os << "(" << r.left << "," << r.top << "," << r.right << "," << r.bottom << ")";
		return os;
	} // operator <<
};