///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: Ship.cpp                                                  //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#include "Ship.h"
#include <cstring>



//-----------------------------------------------------------------------//
// Constructors                                                          //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Constructor instantiating this class. </summary>
/// <param name="icon"> The icon of the ship. </param>

Ship::Ship (const char *name)
{
	mName = new char[80];
	strcpy (mName, name);

	mWidth  = 0;
	mHeight = 0;
	mIcon   = 0;

	mDesign = 0;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Destructor deallocating class resources. </summary>

Ship::~Ship (void)
{
	if (mDesign == 0)
		return;

	for (int x = 0; x < mWidth; ++x)
		delete[] mDesign[x];

	delete[] mDesign;
	delete mName;
}



//-----------------------------------------------------------------------//
// Accessors                                                             //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the name of this ship. </summary>

const char *Ship::name (void) const
{
	return mName;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the icon representing this ship. </summary>

char Ship::icon (void) const
{
	return mIcon;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the width of the design of this ship. </summary>

int Ship::width (void) const
{
	return mWidth;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the height of the design of this ship. </summary>

int Ship::height (void) const
{
	return mHeight;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Gets the position of this ship. </summary>

const Position &Ship::position (void) const
{
	return mPosition;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Sets the position of this ship. </summary>

void Ship::setPosition (Position position)
{
	mPosition = position;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Gets the orientation of this ship. </summary>

Ship::Orientation Ship::orientation (void) const
{
	return mOrien;
}

int Ship::getOrientation(void) 
{
    return (int)mOrien;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Sets the orientation of this ship. </summary>

void Ship::setOrientation (Orientation o)
{
	mOrien = o;
}

bool ** Ship::getDesign()
{
    return mDesign;
}



//-----------------------------------------------------------------------//
// Ship                                                                  //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Determines whether this ship collides with the specified one. This
/// is achieved through the use of a simple bounding box collision algorithm. 
/// </summary>

bool Ship::contains (const Ship *ship)
{
	int x1 = mPosition.x;
	int x2 = mPosition.x + mWidth;
	int y1 = mPosition.y;
	int y2 = mPosition.y + mHeight;

	int sx1 = ship->mPosition.x;
	int sx2 = ship->mPosition.x + ship->mWidth;
	int sy1 = ship->mPosition.y;
	int sy2 = ship->mPosition.y + ship->mHeight;

	return (x1 < sx2 && x2 > sx1 && y1 < sy2 && y2 > sy1);
}



//-----------------------------------------------------------------------//
// Helpers                                                               //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Creates the ship specified by the parameters. </summary>

void Ship::createShip (int width, int height, const char *design)
{
	mWidth  = width;
	mHeight = height;
	int index = 0;

	mDesign = new bool *[mWidth];
	for (int x = 0; x < mWidth; ++x)
		mDesign[x] = new bool[mHeight];

	for (int y = 0; y < mHeight; ++y)
		for (int x = 0; x < mWidth; ++x)
			mDesign[x][y] = design[index++] != 0;
}
