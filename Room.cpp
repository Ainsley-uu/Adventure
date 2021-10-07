#include "Game.h"

// Constructor: Each room is initially disconnected
Rooms::Rooms(int x, int y, int z):loc(x,y,z){
    for( int i=0 ; i<6 ; i++ )
        link[i] = false;
}
    