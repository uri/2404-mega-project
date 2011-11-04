///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: ShipTypes.cpp                                             //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//
 
#include "ShipTypes.h"



// Colonial
//-----------------------------------------------------------------------//
// Battlestar                                                            //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Create ship using the current position and orientation. </summary>

void Battlestar::createShip (void)
{
	mIcon = 'G';
	char design[] =
		{ 1, 1, 1, 1, 1, 1, 1, 1,
		  1, 1, 1, 1, 1, 1, 1, 1 };

	if (mOrien == Ship::North ||
		mOrien == Ship::South)
		 Ship::createShip (8, 2, design);
	else Ship::createShip (2, 8, design);
}



//-----------------------------------------------------------------------//
// Raptor                                                                //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Create ship using the current position and orientation. </summary>

void Raptor::createShip (void)
{
	mIcon = 'P';
	if (mOrien == Ship::East)
	{
		char design[] = { 1, 0, 1, 1, 1, 0 };
		Ship::createShip (2, 3, design);
	}

	else if (mOrien == Ship::North)
	{
		char design[] = { 0, 1, 0, 1, 1, 1 };
		Ship::createShip (3, 2, design);
	}

	else if (mOrien == Ship::West)
	{
		char design[] = { 0, 1, 1, 1, 0, 1 };
		Ship::createShip (2, 3, design);
	}

	else
	{
		char design[] = { 1, 1, 1, 0, 1, 0 };
		Ship::createShip (3, 2, design);
	}
}



//-----------------------------------------------------------------------//
// Viper                                                                 //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Create ship using the current position and orientation. </summary>
void Viper::createShip (void)
{
	mIcon = '^';
	char design[] = { 1, 1, 1 };

	if (mOrien == Ship::North ||
		mOrien == Ship::South)
		 Ship::createShip (1, 3, design);
	else Ship::createShip (3, 1, design);
}



// Cylon
//-----------------------------------------------------------------------//
// Basestar                                                              //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Create ship using the current position and orientation. </summary>

void Basestar::createShip (void)
{
	mIcon = 'B';
	if (mOrien == Ship::North ||
		mOrien == Ship::South)
	{
		char design[] =
			{ 1, 1, 0, 0, 0, 1, 1,
			  0, 0, 1, 1, 1, 0, 0,
			  0, 0, 0, 1, 0, 0, 0,
			  0, 0, 1, 1, 1, 0, 0,
			  1, 1, 0, 0, 0, 1, 1 };

		Ship::createShip (7, 5, design);
	}

	else
	{
		char design[] =
			{ 1, 0, 0, 0, 1,
			  1, 0, 0, 0, 1,
			  0, 1, 0, 1, 0,
			  0, 1, 1, 1, 0,
			  0, 1, 0, 1, 0,
			  1, 0, 0, 0, 1,
			  1, 0, 0, 0, 1 };

		Ship::createShip (5, 7, design);
	}
}



//-----------------------------------------------------------------------//
// HeavyRaider                                                           //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Create ship using the current position and orientation. </summary>

void HeavyRaider::createShip (void)
{
	mIcon = 'H';
	char design[] = { 1, 1, 1, 1 };
	Ship::createShip (2, 2, design);
}



//-----------------------------------------------------------------------//
// Raider                                                                //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Create ship using the current position and orientation. </summary>

void Raider::createShip (void)
{
	mIcon = 'd';
	if (mOrien == Ship::East)
	{
		char design[] = { 1, 0, 1, 1, 1, 0 };
		Ship::createShip (2, 3, design);
	}

	else if (mOrien == Ship::North)
	{
		char design[] = { 0, 1, 0, 1, 1, 1 };
		Ship::createShip (3, 2, design);
	}

	else if (mOrien == Ship::West)
	{
		char design[] = { 0, 1, 1, 1, 0, 1 };
		Ship::createShip (2, 3, design);
	}

	else
	{
		char design[] = { 1, 1, 1, 0, 1, 0 };
		Ship::createShip (3, 2, design);
	}
}
