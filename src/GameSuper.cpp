///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko, UriGorelik                                 //
//   Filename: Game.cpp                                                  //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#include "GameSuper.h"
#include "Board.h"
#include "Player.h"
#include "Random.h"
#include "Renderer.h"
#include "ShipTypes.h"
#include "Statistics.h"
#include <string>
#include <sstream>

#include <limits>
#include <iostream>
using std::endl;
using std::cerr;
using std::cout;
using std::cin;
using std::string;
using std::stringstream;



//-----------------------------------------------------------------------//
// Game                                                                  //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Runs the game and handles restarting it. </summary>



///////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Creates a position and orientation for the specified ship 
/// by querying the user then adding it to the game board. 
/// </summary>

void GameSuper::queryShipPosition (Board *target, Ship *ship)
{
	
	bool built = false;
    
	int x, y; char o; 
	cout << "Enter the location and orientation of the "
    << ship->name() << " (x y o): ";
    
	while (!built)
	{
		while (!(cin >> x >> y >> o))
		{
			cerr << "Invalid input, try again: ";
            
			cin.clear();
			cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
            // Avoid weird looping errors
		}
        
		Ship::Orientation orientation;
		switch (o | 32)
		{
                // Determine the orientation of the ship
			case 'n': orientation = Ship::North; break;
			case 'w': orientation = Ship::West;  break;
			case 's': orientation = Ship::South; break;
			default : orientation = Ship::East;  break;
		}
        
		// Flush the rest of the input stream
		cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        
		// Build and attempt to create the ship
		ship->setPosition (Position (x, y));
		ship->setOrientation (orientation);
        ship->createShip();
        
		if (!target->addShip (ship))
			cerr << "Invalid position, try again: ";
        
		else built = true;
	}
    
	Renderer::draw (mPlayer, mEnemy);
}

///////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Creates a position and orientation for the specified ship
/// by randomization then adding it to the game board. 
/// </summary>

void GameSuper::createShipPosition (Board *target, Ship *ship)
{
//	ship->createShip();
	bool built = false;
    
	while (!built)
	{
		// Generate a position
		int x = random (target->width() - 1);
		int y = random (target->width() - 1);
		int orientation = random (3);
        
        
        
		// Build and attempt to create the ship
		ship->setPosition (Position (x, y));
		ship->setOrientation ((Ship::Orientation) orientation);
        ship->createShip();
		if (target->addShip (ship))
			built = true;
	}
    
}


