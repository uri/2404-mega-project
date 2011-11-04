///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko, Uri Gorelik                                //
//   Filename: Position.h                                                //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef POSITION_H
#define POSITION_H



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a position on the game board. </summary>

//class ostream;
#include <iostream>
using std::ostream;
class Position
{
    
    friend ostream & operator<<( ostream &, const Position &);

public:
	// Constructors
	Position (void);
	Position (int value);
	Position (int x, int y);

public:
	// Variables
	int x;	// X component of the point
	int y;	// Y component of the point
    
public:
    // Operators

};
//ostream & operator<<( ostream &, const Position &);
Position & operator+=(Position & p1, const Position & p2);
Position & operator-=(Position & p1, const Position & p2);
Position & operator*=(Position & p1, const Position & p2);
Position & operator/=(Position & p1, const Position & p2);
Position operator+(const Position & p1, const Position & p2);
Position operator-(const Position & p1, const Position & p2);
Position operator*(const Position & p1, const Position & p2);
Position operator/(const Position & p1, const Position & p2);
bool operator==(const Position & p1, const Position & p2);
bool operator!=(const Position & p1, const Position & p2);
bool operator<(const Position & p1, const Position & p2);
bool operator<=(const Position & p1, const Position & p2);
bool operator>(const Position & p1, const Position & p2);
bool operator>=(const Position & p1, const Position & p2);

Position operator-(const Position & p);
Position & operator--(Position & p);
Position operator--(Position & p ,int l);
Position & operator++(Position & p);
Position operator++(Position & p,int l);

#endif // POSITION_H
