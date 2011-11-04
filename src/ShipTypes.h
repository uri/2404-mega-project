///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: ShipTypes.h                                               //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef SHIP_TYPES_H
#define SHIP_TYPES_H

#include "Ship.h"



//-----------------------------------------------------------------------//
// Colonial                                                              //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a Battlestar ship. </summary>

class Battlestar : public Ship
{
public:
	Battlestar (void) : Ship ("Battlestar") { }
	void createShip (void);
};

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a Raptor ship. </summary>

class Raptor : public Ship
{
public:
	Raptor (void) : Ship ("Raptor") { }
	void createShip (void);
};

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a Viper ship. </summary>

class Viper : public Ship
{
public:
	Viper (void) : Ship ("Viper") { }
	void createShip (void);
};



//-----------------------------------------------------------------------//
// Cylon                                                                 //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a Basestar ship. </summary>

class Basestar : public Ship
{
public:
	Basestar (void) : Ship ("Basestar") { }
	void createShip (void);
};

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a Heavy Raider ship. </summary>

class HeavyRaider : public Ship
{
public:
	HeavyRaider (void) : Ship ("HeavyRaider") { }
	void createShip (void);
};

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a Raider ship. </summary>

class Raider : public Ship
{
public:
	Raider (void) : Ship ("Raider") { }
	void createShip (void);
};

#endif // SHIP_TYPES_H
