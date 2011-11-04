///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: ShipList.cpp                                              //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#include "Ship.h"
#include "ShipList.h"



//-----------------------------------------------------------------------//
// Constructors                                                          //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Constructor instantiating this class. </summary>

ShipList::ShipList (void)
{
	mSize = 0;
	mHead = 0;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Destructor deallocating class resources. </summary>

ShipList::~ShipList (void)
{
	clear();
}



//-----------------------------------------------------------------------//
// ShipList                                                              //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Adds the specified ship to the end of this list. </summary>

void ShipList::add (Ship *ship)
{
	++mSize;
	Node *node = new Node (ship);
	node->mNext = mHead;
	mHead = node;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Removes all elements from this list. </summary>

void ShipList::clear (void)
{
	mSize = 0;
	Node *curr = mHead;
	while (curr != 0)
	{
		mHead = mHead->mNext;

		delete curr->ship;
		delete curr;
		curr = mHead;
	}
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the number of elements in this list. </summary>

int ShipList::size (void) const
{
	return mSize;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Determines if this list is empty. </summary>

bool ShipList::isEmpty (void) const
{
	return mSize == 0;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the first node in this list. </summary>

const ShipList::Node *ShipList::head (void) const
{
	return mHead;
}




