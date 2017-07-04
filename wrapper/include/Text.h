#pragma once

// Basic Text
// Date: 10/95
// Author: Dr. Holly

//------------------------------------------------------------------------
//-- Interface -----------------------------------------------------------
//------------------------------------------------------------------------

class Text
  //! is modeled by string(Character)
  //!   exemplar self
{
public: // Standard Operations
	Text ();
	//! alters self
	//! ensures: self = < >
	~Text ();
	void clear (void);
	//! alters self
	//! ensures: self = < >
	void transferFrom(Text& source);
	//! alters self, source
	//! ensures self = #source  and  source = < >

	// Text Specific Operations
	Text (preserves char* cString);
	//! alters self
	//! preserves cString
	//! requires: cString to be \0 terminated
	//!  ensures: self = cString

	Text& operator = (preserves char* cString);
	//! alters self
	//! preserves cString
	//! requires: cString to be \0 terminated
	//!  ensures: self = cString

	Text& operator = (preserves Text& rhs);
	//! alters self
	//! ensures: self = rhs

	Boolean operator == (preserves Text& rhs);
	//! preserves self
	//! ensures: "operator ==" = (self = rhs)

	Boolean operator == (preserves char* cString);
	//! preserves self
	//! ensures: "operator ==" = (self = cString)

	friend 	Boolean operator == (preserves char* lhs, preserves Text& rhs);
	//! ensures: "operator ==" = (lhs = rhs)

	Boolean operator != (preserves Text& rhs);
	//! preserves self
	//! ensures: "operator !=" = (self = rhs)

	Boolean operator != (preserves char* cString);
	//! preserves self
	//! ensures: "operator !=" = (self <> cString)

	friend 	Boolean operator != (preserves char* lhs, preserves Text& rhs);
	//! ensures: "operator !=" = (lhs <> rhs)

	Boolean operator < (preserves Text& rhs);
	//! preserves self
	//! ensures: "operator <" = (self < rhs)

	Boolean operator < (preserves char* cString);
	//! preserves self
	//! ensures: "operator <" = (self < cString)

	friend 	Boolean operator < (preserves char* lhs, preserves Text& rhs);
	//! ensures: "operator <" = (lhs < rhs)

	Boolean operator <= (preserves Text& rhs);
	//! preserves self
	//! ensures: "operator <=" = (self <= rhs)

	Boolean operator <= (preserves char* cString);
	//! preserves self
	//! ensures: "operator <=" = (self <= cString)

	friend 	Boolean operator <= (preserves char* lhs, preserves Text& rhs);
	//! ensures: "operator <=" = (lhs <= rhs)

	Boolean operator > (preserves Text& rhs);
	//! preserves self
	//! ensures: "operator >" = (self > rhs)

	Boolean operator > (preserves char* cString);
	//! preserves self
	//! ensures: "operator >" = (self > cString)

	friend 	Boolean operator > (preserves char* lhs, preserves Text& rhs);
	//! ensures: "operator >" = (lhs > rhs)

	Boolean operator >= (preserves Text& rhs);
	//! preserves self
	//! ensures: "operator >=" = (self >= rhs)

	Boolean operator >= (preserves char* cString);
	//! preserves self
	//! ensures: "operator >=" = (self >= cString)

	friend 	Boolean operator >= (preserves char* lhs, preserves Text& rhs);
	//! ensures: "operator >=" = (lhs >= rhs)

	void add (
			preserves Integer position,
			preserves Character c
		);
	//! alters self
	//!  requires:  0 <= position <= |self|
	//! ensures:   there exists a, b: string(Character)
	//!             (|a| = position  and  #self = a * b  and  self = a * <#c> * b)

	void remove (
			preserves Integer position,
			produces Character& c
		);
	//! alters self
	//!  requires:  0 <= position < |self|
	//! ensures:   there exists a, b: string(Character)
	//!             (|a| = position  and  #self = a * <c> * b  and  self = a * b)

	Integer size (void);
	//! preserves self
	//! ensures:   size = |self|

	void append (preserves Text& from);
	//! preserves	from
	//! ensures:	self = #self * from

	void copyToCString (alters char* to_cString);
	//! preserves	self
	//! requires:	|to_cString| > |self|
	//!  ensures:	to_cString = self

	friend std::ostream& operator << (
			alters std::ostream& s,
			preserves Text& x
		);

	friend std::istream& operator >> (
			alters std::istream& s,
			alters Text& x
		);

	operator char* ();
	//! preserves self
	//! ensures:   char* () = rep->cString

private:
   // local operations
	void createNewRep(char* cString);
	void reclaimRepsString(void);
	void convertToListRep (void);
	void convertToCStringRep (void);
	void moveCurrentIntoPosition (
			Integer position
		);
   // Unimplemented local operations
	Text (const Text& s);
	Text* operator & (void);
	const Text* operator & (void) const;

private:	// Representation
	class NodeRep;
	typedef NodeRep* Node;
	class NodeRep {
	public:
		Character c;
		Node target;
	};

	class CharacterListRep {
	public:
		Node smartNode;
		Node current;
		Integer position;
	};

	class Text_Rep {
	public:
		char* cString;
		CharacterListRep s;
		Boolean inListRep;
		Integer length;
	};

	Text_Rep* rep;
};



