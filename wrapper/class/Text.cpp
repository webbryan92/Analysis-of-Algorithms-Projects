// Basic Text
// Date: 10/95
// Author: Dr. Holly
#include "wrapper.h"

// Convention
/*
When !inListRep, linked list rep looks like the following:

rep.s
					|----|     |-------------|
 s.smartNode  |  *-+---->|      | NULL |
					|----|     |-------------|
 s.current		|  *-+-----------^
					|----|
 s.position		|  0 |
					|----|


When inListRep, cString rep looks like the following:
rep.cString = NULL;
*/

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------


void Text::createNewRep(char* cString)
{
	rep = new Text_Rep;	
	rep->length = (int)strlen(cString);
	rep->cString = (char *)new char[rep->length + 1];
	strcpy (rep->cString, cString);

	rep->s.smartNode = new NodeRep;
	rep->s.smartNode->target = NULL;
	rep->s.current = rep->s.smartNode;
}

//-----------------------------------------------------------------------

void Text::reclaimRepsString ()
{
	Node p;
	Node old_node;

	// Dispose of Linked List
	p = rep->s.smartNode;
	while (p != NULL) {
		old_node = p;
		p = p->target;
		delete old_node;
	}	// end while

	// Dispose of cString
	delete [] rep->cString;

	delete rep;
}	// ~Text

//-----------------------------------------------------------------------

void Text::convertToListRep (void)
{
	Node p;
	Node new_node;
	Integer i;

	p = rep->s.smartNode;
	for (i = 0; i < rep->length; i++) {
		new_node = new NodeRep;
		new_node->c = rep->cString[i];
		p->target = new_node;
		p = new_node;
	}	// end for
	// NULL at end of linked list
	p->target = NULL;

	delete [] rep->cString;
	rep->cString = NULL;
	rep->inListRep = true;
}	// convertToListRep

//-----------------------------------------------------------------------

void Text::convertToCStringRep (void)
{
	Node p;
	Node old_node;
	Integer i;
	Character c;

	rep->cString = (char *)new char[rep->length + 1];
	p = rep->s.smartNode->target;
	rep->s.smartNode->target = NULL;
	rep->s.current = rep->s.smartNode;
	rep->s.position = 0;

	for (i = 0; i < rep->length; i++) {
		rep->cString[i] = p->c;
		old_node = p;
		p = p->target;
	  delete old_node;
	}	// end for

	rep->cString[rep->length] = '\0';
	rep->inListRep = false;
}	// convertToCStringRep

//-----------------------------------------------------------------------

void Text::moveCurrentIntoPosition (
		Integer position
	)
{
	Integer i;

	if (!rep->inListRep) {
		convertToListRep ();
	} else {
	// already inListRep
		if (rep->s.position > position) {
			rep->s.position = 0;
			rep->s.current = rep->s.smartNode;
		}	// end if
	}	// end if
	// Move into position
	for (i = rep->s.position; i < position; i++) {
		rep->s.current = rep->s.current->target;
	}	// end for
	rep->s.position = position;
}	// moveCurrentIntoPosition

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

Text::Text ()
{
	createNewRep("");
}	// Text

//-------------------------------------------------------------------------

Text::Text (
		char* cString
	)
{
	createNewRep(cString);
}	// Text

//-------------------------------------------------------------------------

Text::~Text ()
{
	reclaimRepsString();
}	// ~Text

//-------------------------------------------------------------------------

Text& Text::operator = (
			preserves char* cString
		)
{
	self.reclaimRepsString();
	self.createNewRep(cString);

	return (self);
}	// operator =

//-------------------------------------------------------------------------

Text& Text::operator = (
      preserves Text& rhs
   )
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();
	self.reclaimRepsString();
	self.createNewRep(rhs.rep->cString);
	return (self);
}	// operator = 

//-------------------------------------------------------------------------

void Text::transferFrom(Text& source)
{
	if (source.rep->inListRep)
		source.convertToCStringRep ();
	self.reclaimRepsString();
	self.createNewRep(source.rep->cString);
	source.reclaimRepsString();
	source.createNewRep("");
}	// transferFrom

//-------------------------------------------------------------------------

void Text::clear (void)
{
	self.reclaimRepsString();
	self.createNewRep("");
}	// clear

//-------------------------------------------------------------------------

Boolean Text::operator == (
			preserves Text& rhs
		)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (rep->cString, rhs.rep->cString) == 0);
}	// operator ==

//-------------------------------------------------------------------------

Boolean Text::operator == (
			preserves char* cString
		)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return (strcmp (rep->cString, cString) == 0);
}	// operator ==

//-------------------------------------------------------------------------

Boolean operator == (
			preserves char* lhs,
			preserves Text& rhs
		)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (lhs, rhs.rep->cString) == 0);
}	// operator ==

//-------------------------------------------------------------------------

Boolean Text::operator != (
			preserves Text& rhs
		)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (rep->cString, rhs.rep->cString) != 0);
}	// operator !=

//-------------------------------------------------------------------------

Boolean Text::operator != (
			preserves char* cString
		)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return (strcmp (rep->cString, cString) != 0);
}	// operator !=

//-------------------------------------------------------------------------

Boolean operator != (
			preserves char* lhs,
			preserves Text& rhs
		)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (lhs, rhs.rep->cString) != 0);
}	// operator !=

//-------------------------------------------------------------------------

Boolean Text::operator < (
			preserves Text& rhs
		)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (rep->cString, rhs.rep->cString) < 0);
}	// operator <

//-------------------------------------------------------------------------

Boolean Text::operator < (
			preserves char* cString
		)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return (strcmp (rep->cString, cString) < 0);
}	// operator <

//-------------------------------------------------------------------------

Boolean operator < (
			preserves char* lhs,
			preserves Text& rhs
		)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (lhs, rhs.rep->cString) < 0);
}	// operator <

//-------------------------------------------------------------------------

Boolean Text::operator <= (
			preserves Text& rhs
		)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (rep->cString, rhs.rep->cString) <= 0);
}	// operator <=

//-------------------------------------------------------------------------

Boolean Text::operator <= (
			preserves char* cString
		)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return (strcmp (rep->cString, cString) <= 0);
}	// operator <=

//-------------------------------------------------------------------------

Boolean operator <= (
			preserves char* lhs,
			preserves Text& rhs
		)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (lhs, rhs.rep->cString) <= 0);
}	// operator <=

//-------------------------------------------------------------------------

Boolean Text::operator > (
			preserves Text& rhs
		)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (rep->cString, rhs.rep->cString) > 0);
}	// operator >

//-------------------------------------------------------------------------

Boolean Text::operator > (
			preserves char* cString
		)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return (strcmp (rep->cString, cString) > 0);
}	// operator >

//-------------------------------------------------------------------------

Boolean operator > (
			preserves char* lhs,
			preserves Text& rhs
		)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (lhs, rhs.rep->cString) > 0);
}	// operator >

//-------------------------------------------------------------------------

Boolean Text::operator >= (
			preserves Text& rhs
		)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (rep->cString, rhs.rep->cString) >= 0);
}	// operator >=

//-------------------------------------------------------------------------

Boolean Text::operator >= (
			preserves char* cString
		)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return (strcmp (rep->cString, cString) >= 0);
}	// operator >=

//-------------------------------------------------------------------------

Boolean operator >= (
			preserves char* lhs,
			preserves Text& rhs
		)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return (strcmp (lhs, rhs.rep->cString) >= 0);
}	// operator >=

//-------------------------------------------------------------------------

void Text::add (
		Integer position,
		Character c
	)
{
	Node new_node;

	moveCurrentIntoPosition (position);
	new_node = new NodeRep;
	new_node->c = c;
	new_node->target = rep->s.current->target;
	rep->s.current->target = new_node;
	rep->length++;
}	// add

//-------------------------------------------------------------------------

void Text::remove (
		Integer position,
		Character& c
	)
{
	Node old_node;

	moveCurrentIntoPosition (position);
	old_node = rep->s.current->target;
	rep->s.current->target = old_node->target;
	c = old_node->c;
	delete old_node;
	rep->length--;
}	// remove

//-------------------------------------------------------------------------

Integer Text::size (void)
{
	return (rep->length);
}	// size

//-------------------------------------------------------------------------

void Text::append (
			preserves Text& from
		)
{
	char* cString;
	Integer length;

	if (rep->inListRep)
		convertToCStringRep ();
	if (from.rep->inListRep)
		from.convertToCStringRep ();

	length = (int)strlen (rep->cString) + 
			 (int)strlen (from.rep->cString);
	cString = (char *)new char[length + 1];
	strcpy (cString, rep->cString);
	strcat (cString, from.rep->cString);

	// Dispose of original cString
	delete [] rep->cString;

	rep->cString = cString;
	rep->length = (int)strlen (rep->cString);
}  // append

//-------------------------------------------------------------------------

void Text::copyToCString (
			alters char* to_cString
		)
{
	if (rep->inListRep)
		convertToCStringRep ();
	strcpy (to_cString, rep->cString);
}  // copyToCString

//-------------------------------------------------------------------------

Text::operator char* () 
{ 
	if (rep->inListRep)
		convertToCStringRep ();

	return (rep->cString);
} // operator char* ()

//-------------------------------------------------------------------------

std::ostream& operator << (
         alters std::ostream& os,
         preserves Text& x
      )
{
 	if (x.rep->inListRep)
		x.convertToCStringRep ();

	os << "\"" << x.rep->cString << "\"";
   return (os);
}  // operator <<

//-------------------------------------------------------------------------

std::istream& operator >> (
         alters std::istream& s,
         alters Text& x
      )
{
	char input_line[100];

	std::cin.getline (input_line, 99);
	x = input_line;
	return (s);
}  // operator >>

