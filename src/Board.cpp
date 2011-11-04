///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: Board.cpp                                                 //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#include "Ship.h"
#include "Board.h"
#include "Position.h"
#include "ShipList.h"



//-----------------------------------------------------------------------//
// Constructors                                                          //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Constructor instantiating this class. </summary>

Board::Board (void)
{
	mWidth  = 25;
	mHeight = 15;
	mShips = new List<Ship *>();
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Destructor deallocating class resources. </summary>

Board::~Board (void)
{
    delete mShips;
}



//-----------------------------------------------------------------------//
// Accessors                                                             //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the width of the field. </summary>

int Board::width (void) const
{
	return mWidth;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the height of the field. </summary>

int Board::height (void) const
{
	return mHeight;
}


List<Ship *> * Board::getShipList(void)
{
    return mShips;
}



//-----------------------------------------------------------------------//
// Board                                                                 //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Adds the specified ship to the list. All added ships will be deleted
/// when this object is destroyed. 
/// </summary>
/// <returns> False if the ships position is invalid, true otherwise. </returns>

bool Board::addShip (Ship *ship)
{
	//int xPos = ship->mPosition.x;
	//int yPos = ship->mPosition.y;

	// Check ships bounds
	if (ship->mPosition.x < 0 || ship->mPosition.x > mWidth ||
		ship->mPosition.y < 0 || ship->mPosition.y > mHeight)
		return false;

	if (ship->mPosition.x + ship->mWidth  < 0 || ship->mPosition.x + ship->mWidth  > mWidth  ||
		ship->mPosition.y + ship->mHeight < 0 || ship->mPosition.y + ship->mHeight > mHeight)
		return false;
	
	// Check ships position
	for (const List<Ship *>::ListNode<Ship *> *node = mShips->head(); node != 0; node = node->next())
		if (ship->contains (node->data)) return false;

	// Add the ship
	mShips->add (ship);
	return true;
}
