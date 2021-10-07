#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <string>
using namespace std; 

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3
#define UP 4
#define DOWN 5

class Coordinate{
private:
    int x, y, z;
public:
    Coordinate(){}
    Coordinate(int a, int b, int c); 
    bool operator==(const Coordinate& that) const;
    bool operator!=(const Coordinate& that) const;
    friend class Map;
    friend class Adventure;
    ~Coordinate(){}
};

class Rooms
{
private:
    Coordinate loc;
    bool link[6];
public:
    Rooms(int x=0, int y=0, int z=0);
    friend class Map;
    friend class Adventure;
    ~Rooms(){}
};

class Map
{
private:
    int mapSize, mapHeight;
    Rooms *rooms;
    Coordinate Lobby;   // Lobby location
    Coordinate Monster; // Monster location
    Coordinate Princess;  // Princess location
public:
    Map(int s = 0, int h = 0);
    void RoomAllocation();  // This function is used to allocate rooms
    int RoomNum(int x, int y, int z) const; // Calculate the room number from the location information x, y, z
    int RoomNum( const Coordinate& room ) const;    // Overloaded function
    void Link(const Coordinate& terminal);  // Plan two paths from Lobby to Monster and Princess
    void RandomLink();  // Randomly connect rooms
    friend class Adventure;
    ~Map();
};

class Adventure
{
private:
    Map *map;
    Coordinate curLoc;
    void Loop();    // Main game loop
    int ExitsNum( );    // Calculate the export quantity
    void CoutExits();   // Export each export direction
    int Direction(const string& s); // The selected direction is obtained by user input
public:
    Adventure(){}
    void Initialize();  // Game initialization
    void Start();   // Game start
    ~Adventure(){}
};

#endif