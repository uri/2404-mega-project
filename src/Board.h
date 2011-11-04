///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: Board.h                                                   //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef BOARD_H
#define BOARD_H



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//

#include "List.h"

class Ship;
class Position;
class ShipList;

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a single game board. </summary>

class Board
{
public:
	// Constructors
	 Board			(void);
	~Board			(void);

	// Accessors
	int     width		(void) const;
	int     height		(void) const;
    
//    ShipList * getShipList(void); // Accessor for the shiplist
    List<Ship *> * getShipList(void);

	// Board
	bool addShip	(Ship *ship);

	friend class Renderer;
    friend class Player;        // So player can access the player list

private:
	int mWidth;			// Width  of the board
	int mHeight;		// Height of the board

    List<Ship *> *mShips;
//	ShipList *mShips;           // List of ships on the board
};

#endif // BOARD_H
