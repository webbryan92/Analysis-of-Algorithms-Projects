#pragma once
#include "Wrapper.h"

class Point: public POINT
{
	// Inherits the representation from Window's POINT
	// POINT's representation is: int x, y

	// Adds the following operations: constructor, clear, operator =, transferFrom, operator <<
	// Use Point whereever a Windows program calls for a POINT

private:
	void initializeRep()
		// ensures: self = (0, 0)
	{
		x = 0;
		y = 0;
	} // initializeRep

	void copyRep (Point& from)
		// ensures: self = from
	{
		x = from.x;
		y = from.y;
	} // copyRep

public:
	Point()
		// ensures: self = (0, 0)
	{
		initializeRep();
	} // Point()

	void clear(void)
		// ensures: self = (0, 0)
	{
		initializeRep();	
	} // clear

	Point& operator = (Point& rhs)
		// ensures: self = rhs
	{
		copyRep(rhs);	
		return (*this);
	} // operator =

	void transferFrom(Point& source)
		// ensures: self = source and source = (0, 0)
	{
		copyRep(source);	
		source.initializeRep();
	} // transferFrom

	friend ostream& operator << (ostream &os, Point& r)
	{
		os << "(" << r.x << "," << r.y << ")";
		return os;
	} // operator <<
};