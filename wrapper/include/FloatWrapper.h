#pragma once

/*
Declaration of wrapper for float
Author: Dr. Holly
*/

class Float
{
public:
	Float (float x = 0.0) { f = x; };
	Float (const Float& x) { f = x.f; };
	inline ~Float () {};

	void clear (void) { f = 0.0; };
	void transferFrom(Float& source) {f = source.f; source.clear();};


	void operator += (const Float& rhs) { f += rhs.f; };
	void operator -= (const Float& rhs) { f -= rhs.f; };
	void operator *= (const Float& rhs) { f *= rhs.f; };
	void operator /= (const Float& rhs) { f /= rhs.f; };


	inline operator float () const { return f; };

private:
	float f;
}; // class Float

std::istream& operator >> (
         alters std::istream& s,
         alters Float& x
      );



