#pragma once
/*
Declaration of wrapper for the scalar type long
Author: Dr. Holly
*/

class LongInteger
{
public:
	LongInteger (long x = 0) { i = x; };
	LongInteger (const LongInteger &x) { i = x.i; };
	inline ~LongInteger () {};

	void clear (void) {	i = 0; };
	void transferFrom(LongInteger& source) {i = source.i; source.clear();};

	void operator += (const LongInteger& rhs) { i += rhs.i; };
	void operator -= (const LongInteger& rhs) { i -= rhs.i; };
	void operator *= (const LongInteger& rhs) { i *= rhs.i; };
	void operator /= (const LongInteger& rhs) { i /= rhs.i; };
	void operator %= (const LongInteger& rhs) { i %= rhs.i; };

	LongInteger operator ++ ()    { i++; return LongInteger(i);};     // prefix ++x
	LongInteger operator ++ (int) { i++; return LongInteger(i-1);};   // postfix x++
	LongInteger operator -- ()    { i--; return LongInteger(i); };    // prefix --x
	LongInteger operator -- (int) { i--; return LongInteger(i+1); };  // postfix x--

	inline operator long int () const { return i; };

private:
	long int i;

}; // class LongInteger

std::istream& operator >> (
         alters std::istream& s,
         alters LongInteger& x
      );

