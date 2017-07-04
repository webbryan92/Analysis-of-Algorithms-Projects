#pragma once
/*
Declaration of wrapper for the scalar type int
Author: Dr. Holly
*/

class Integer
{
public:
	Integer (int x = 0) { i = x; };
	Integer (const Integer &x) { i = x.i; };
	inline ~Integer () {};

	void clear (void) {	i = 0; };
	void transferFrom(Integer& source) {i = source.i; source.clear();};

	void operator += (const Integer& rhs) { i += rhs.i; };
	void operator -= (const Integer& rhs) { i -= rhs.i; };
	void operator *= (const Integer& rhs) { i *= rhs.i; };
	void operator /= (const Integer& rhs) { i /= rhs.i; };
	void operator %= (const Integer& rhs) { i %= rhs.i; };

	Integer operator ++ ()    { i++; return Integer(i);};     // prefix ++x
	Integer operator ++ (int) { i++; return Integer(i-1);};   // postfix x++
	Integer operator -- ()    { i--; return Integer(i); };    // prefix --x
	Integer operator -- (int) { i--; return Integer(i+1); };  // postfix x--

	inline operator int () const { return i; };

private:
	int i;
}; // class Integer

std::istream& operator >> (
         alters std::istream& s,
         alters Integer& x
      );


