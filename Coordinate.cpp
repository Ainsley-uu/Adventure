#include "Game.h"

// Constructor: coordinate initialization
Coordinate::Coordinate(int a, int b, int c):x(a), y(b), z(c){}

bool Coordinate::operator==(const Coordinate& that) const{
    return ( x==that.x ) && ( y==that.y ) && ( z==that.z );
}

bool Coordinate::operator!=(const Coordinate& that) const{
    return ( x!=that.x ) || ( y!=that.y ) || ( z!=that.z );
}