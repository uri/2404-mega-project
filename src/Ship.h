///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: Ship.h                                                    //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef SHIP_H
#define SHIP_H

#include "Position.h"



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents an abstract ship. </summary>

class Ship
{
public:
	// Enumerations
	///////////////////////////////////////////////////////////////////////////
	/// <summary> Specifies the orientation of the ship. </summary>

	enum Orientation
	{
		East,	//   0 Degrees
		North,	//  90 Degrees
		West,	// 180 Degrees
		South,	// 270 Degrees
	};

public:
	// Constructors
	 Ship (const char *name);
	~Ship (void);

	// Accessors
	const char *name (void) const;

	char icon	(void) const;
	int  width	(void) const;
	int  height	(void) const;
    bool ** getDesign(void);

	const Position &position (void) const;
	void setPosition (Position position);

	Orientation orientation (void) const;
    int getOrientation(void);
	void setOrientation (Orientation o);
		
	// Ship
	bool contains (const Ship *ship);
	virtual void createShip (void) = 0;

	friend class Board;
	friend class Renderer;

protected:
	// Helpers
	void createShip (int width, int height, const char *design);

protected:
	// Variables
	char *mName;		// Ship name
	char mIcon;			// Ship icon
	int mWidth;			// Ship width
	int mHeight;		// Ship height

	bool **mDesign;		// Ship design

	Position mPosition;	// Ship position
	Orientation mOrien;	// Ship orientation
};

#endif // SHIP_H
