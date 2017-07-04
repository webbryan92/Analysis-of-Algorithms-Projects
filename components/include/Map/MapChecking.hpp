#pragma once

//
// checking version of Map 
// author: Dr. Holly
//

template <
	template <class, class, class> class Map,
	class K,
	class V,
	class TCompare
>
class MapChecking1:
	public Map <K, V, TCompare>
{
	typedef Map <K, V, TCompare> MapInstance;
public:

//-------------------------------------------------------------------

void add (consumes K& key, consumes V& value)
{
	// assert that key is not defined in map m
	if (MapInstance::hasKey (key)) {
		OutputDebugString ("Operation: add\n");
		OutputDebugString ("Assertion failed: !hasKey(key)\n");
		DebugBreak ();
	}	// end if 

	MapInstance::add (key, value);
}	// add

//-------------------------------------------------------------------

void remove (preserves K& key,	produces K& dCopy, produces V& value)
{
	// assert that key is defined in map m
	if (!MapInstance::hasKey (key)) {
		OutputDebugString ("Operation: remove\n");
		OutputDebugString ("Assertion failed: hasKey(key)\n");
		DebugBreak ();
	}	// end if 

	MapInstance::remove (key, dCopy, value);
}	// remove

//-------------------------------------------------------------------

V& value (preserves K& key)
{
	// assert that key is defined in map m
	if (!MapInstance::hasKey (key)) {
		OutputDebugString ("Operation: value\n");
		OutputDebugString ("Assertion failed: hasKey(key)\n");
		DebugBreak ();
	}	// end if 

	return (MapInstance::value(key));
}	// value

//-------------------------------------------------------------------

void removeAny (
		produces K& key,
		produces V& value
	)
{
	// assert that |m| > 0
	if (MapInstance::size () <= 0) {
		OutputDebugString ("Operation: removeAny\n");
		OutputDebugString ("Assertion failed: |m| > 0\n");
		DebugBreak ();
	}	// end if 

	MapInstance::removeAny (key, value);
}	// removeAny
};

