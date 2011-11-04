///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko, Uri Gorelik                                //
//   Filename: Position.cpp                                              //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#include "Position.h"
//#include <iostream>
#include <string.h>

using std::ostream;

//-----------------------------------------------------------------------//
// Constructors                                                          //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> 
/// Constructor instantiating this class. Setting both components to zero. 
/// </summary>

Position::Position (void)
{
	x = y = 0;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Constructor instantiating this class. </summary>
/// <param name="value"> Value to initialize both components to. </param>

Position::Position (int value)
{
	x = y = value;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Constructor instantiating this class. </summary>
/// <param name="x"> Initial value for the x component. </param>
/// <param name="y"> Initial value for the y component. </param>

Position::Position (int x, int y)
{
	this->x = x;
	this->y = y;
}

//-----------------------------------------------------------------------//
// Operators                                                             //
//-----------------------------------------------------------------------//

ostream & operator<<( ostream & output, const Position & p) {
    output << "(" << p.x << ", " << p.y << ")";
    return output;
}

Position & operator+=(Position &p1, const Position & p2) {
    p1.x = p1.x + p2.x;
    p1.y = p1.y + p2.y;
    
    return p1;
}

Position & operator-=(Position & p1, const Position & p2) {
    p1.x = p1.x - p2.x;
    p1.y = p1.y - p2.y;
    return p1;
}

Position & operator*=(Position & p1, const Position & p2) {
    p1.x = p1.x * p2.x;
    p1.y = p1.y * p2.y;
    return p1;
}

Position & operator/=(Position & p1, const Position & p2) {
    p1.x = p1.x / p2.x;
    p1.y = p1.y / p2.y;
    return p1;
}

Position operator+(Position & p1, const Position & p2) {
    return Position(p1.x + p2.x, p1.y + p2.y);
}

Position operator-(Position & p1, const Position & p2) {
        return Position(p1.x - p2.x, p1.y - p2.y);
}

Position operator*(const Position & p1, const Position & p2) {
        return Position(p1.x * p2.x, p1.y * p2.y);
}

Position operator/(Position & p1, const Position & p2) {
        return Position(p1.x / p2.x, p1.y / p2.y);
}

bool operator==(const Position & p1, const Position & p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

bool operator!=(const Position & p1, const Position & p2) {
    return (p1.x != p2.x || p1.y != p2.y);
}

bool operator<(const Position & p1, const Position & p2) {
    int p1val = (p1.x*p1.x) + (p1.y*p1.y);
    int p2val = (p2.x*p2.x) + (p2.y*p2.y);
    
    return (p1val < p2val);
}

bool operator<=(const Position & p1, const Position & p2) {
    if (p1.x == 0 && p1.y == 0) return true;
    return p1 < p2;
}
bool operator>(const Position & p1, const Position & p2) {
    int p1val = (p1.x*p1.x) + (p1.y*p1.y);
    int p2val = (p2.x*p2.x) + (p2.y*p2.y);
    
    return (p1val > p2val);
}

bool operator>=(const Position & p1, const Position & p2) {
    if (p1.x == 0 && p1.y == 14) return true;
    return p1 > p2;
}

Position operator-(const Position & p) {
    return Position(-p.x, -p.y);
}

Position & operator--(Position & p) {
    p.x = p.x - 1;
    p.y = p.y - 1;
    return p;
}

Position operator--(Position & p ,int l) {
    Position returning = Position(p.x,p.y);
    p.x = p.x - 1;
    p.y = p.y - 1;
    
    return returning;
}
Position & operator++(Position & p) {
    p.x = p.x + 1;
    p.y = p.y + 1;
    return p;   
}

Position operator++(Position & p,int l) {
    Position returning = Position(p.x,p.y);
    ++p;
    
    return returning;
}



