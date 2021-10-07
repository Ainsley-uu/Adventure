#include "Game.h"

void Map::Link(const Coordinate& terminal)
{
    Coordinate current = Lobby;
    while( current.x < terminal.x ){
        rooms[RoomNum(current)].link[0] = true;
        current.x++;
        rooms[RoomNum(current)].link[1] = true;
    }

    while( current.x > terminal.x ){
        rooms[RoomNum(current)].link[1] = true;
        current.x--;
        rooms[RoomNum(current)].link[0] = true;
    }

    while( current.y < terminal.y ){
        rooms[RoomNum(current)].link[3] = true;
        current.y++;
        rooms[RoomNum(current)].link[2] = true;
    }

    while( current.y > terminal.y ){
        rooms[RoomNum(current)].link[2] = true;
        current.y--;
        rooms[RoomNum(current)].link[3] = true;
    }

    while( current.z < terminal.z ){
        rooms[RoomNum(current)].link[4] = true;
        current.z++;
        rooms[RoomNum(current)].link[5] = true;
    }

    while( current.z > terminal.z ){
        rooms[RoomNum(current)].link[5] = true;
        current.z--;
        rooms[RoomNum(current)].link[4] = true;
    }
}

// Randomly connect rooms
void Map::RandomLink()
{
    for( int i=0 ; i<mapHeight*mapSize*mapSize ; i++ ){
        // Randomly pick room coordinates
        int x = rand() % (mapSize-1);
        int y = rand() % (mapSize-1); 
        int z = rand() % (mapHeight-1); 
        // Randomly select the number of room connections
        int linkNum = rand() % 5;
        
        for( int j=0 ; j<linkNum ; j++ ){
            // Randomly select the direction of room connection
            int link = rand() % 6;
            switch( link ){
                case EAST:{
                    rooms[RoomNum(x,y,z)].link[3] = true;
                    rooms[RoomNum(x,y+1,z)].link[2] = true;
                    break;
                }
                case SOUTH:{
                    rooms[RoomNum(x,y,z)].link[1] = true;
                    rooms[RoomNum(x-1,y,z)].link[0] = true;
                    break; 
                }
                case WEST:{
                    rooms[RoomNum(x,y,z)].link[2] = true;
                    rooms[RoomNum(x,y-1,z)].link[3] = true;
                    break;
                }
                case NORTH:{
                    rooms[RoomNum(x,y,z)].link[0] = true;
                    rooms[RoomNum(x+1,y,z)].link[1] = true;
                    break;
                }
                case UP:{
                    rooms[RoomNum(x,y,z)].link[4] = true;
                    rooms[RoomNum(x,y,z+1)].link[5] = true;
                    break;
                }
                case DOWN:{
                    rooms[RoomNum(x,y,z)].link[5] = true;
                    rooms[RoomNum(x,y,z-1)].link[4] = true;
                    break;
                }
            }
        }

    }
}

// Calculate the room number from the location information x, y, z
int Map::RoomNum( const Coordinate& room ) const
{
    return room.x + room.y*mapSize + room.z*mapSize*mapSize;
}

// Overloaded function
int Map::RoomNum(int x, int y, int z) const 
{
    return x + y*mapSize + z*mapSize*mapSize; 
}

// Allocate rooms
void Map::RoomAllocation()
{
    // Random seeding
    srand((unsigned)time(NULL)); 

    // Create a room based on the size of the map
    rooms = new Rooms[mapSize*mapSize*mapHeight];
    for( int i=0 ; i<mapSize ; i++ )
        for( int j=0 ; j<mapSize ; j++ )
            for( int k=0 ; k<mapHeight ; k++ )
                rooms[RoomNum(i,j,k)].loc = Coordinate(i,j,k);
            
    // The lobby is in the center
    Lobby = Coordinate( mapSize/2 , mapSize/2 , mapHeight/2 );
    
    // Randomly generate Monster position
    do{
        Monster = Coordinate(rand()%(mapSize), rand()%(mapSize), rand()%(mapHeight));
    }while( Monster == Lobby );
    // cout << "Monster" << Monster.x << " " << Monster.y << " " << Monster.z << endl;

    // Randomly generate Princess position
    do{
        Princess = Coordinate(rand()%(mapSize), rand()%(mapSize), rand()%(mapHeight));
    }while(Princess == Lobby || Princess == Monster );
    // cout << "Princess" << Princess.x << " " << Princess.y << " " << Princess.z << endl;

    // Plan two paths from Lobby to Monster and Princess 
    Link(Princess);
    Link(Monster);

    // Randomly connect rooms
    RandomLink();
}

Map::Map(int s, int h):mapSize(s), mapHeight(h)
{
    RoomAllocation();
}

