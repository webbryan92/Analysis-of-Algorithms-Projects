#pragma once

/*
Declaration of wrapper for the scalar type char
Author: Dr. Holly
*/

class Character
{
public:
	Character (char x = 0) { c = x; };
	Character (const Character &x) { c = x.c; };
	inline ~Character () {};

	void clear (void) { c = 0; };	
	void transferFrom(Character& source) {c = source.c; source.clear();};

	Character operator ++ () { c++;	return Character(c); };          // prefix ++x
	Character operator ++ (int) { c++; return Character (c - 1); };       // postfix x++
	Character operator -- () { c--; return Character(c); };          // prefix --x
	Character operator -- (int) { c--; return Character(c+1); };       // postfix x--

	void operator += (const Character& rhs) { c += rhs.c; };
	void operator -= (const Character& rhs) { c -= rhs.c; };
	void operator *= (const Character& rhs) { c *= rhs.c; };
	void operator /= (const Character& rhs) { c -= rhs.c; };
	void operator %= (const Character& rhs) { c %= rhs.c; };

	inline operator char() const { return (c); };

	friend std::ostream& operator << (
			alters std::ostream& s,
			preserves Character& x
		);

	friend std::istream& operator >> (
         alters std::istream& s,
         alters Character& x
      );

private:
   char c;
}; // class Character



