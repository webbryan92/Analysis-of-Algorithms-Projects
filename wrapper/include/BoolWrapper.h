#pragma once

/*
Declaration of scalar type Boolean
Author: Dr. Holly
*/

class Boolean
{
public:
	Boolean (const Boolean &x) {b = x.b;};
	Boolean (bool x = false) {b = x ? true : false;};
	Boolean (int x) {b = x ? true : false;};
	inline ~Boolean () {};
	void clear (void) {	b = false; };
	void transferFrom(Boolean& source) {b = source.b; source.clear();};

	operator bool() const {return (b);};

private:
   bool b;
};

std::ostream& operator << (
         alters std::ostream& s,
         preserves Boolean& x
      );

std::istream& operator >> (
         alters std::istream& s,
         alters Boolean& x
      );



