#include "Game.h"

string Dire[]={"north","south","west","east","up","down"};
string RoomType[]={ "bedroom", "ballroom", "den", "restaurant", "bathroom", "bar"};

// Game initialization
void Adventure::Initialize()
{
    int side, height,flag;
    char opt;
    cout << "Welcome to the mysterious castle. Let's start a wonderful journey" << endl;
    while(1){
        cout << "If you are ready, please enter '!', otherwise enter 'h' for help" << endl;
        cin >> opt;
        if( opt == '!' )
            break;
        else{
            cout << "Game task: find the princess and take her out of the castle, if you encounter a monster during the game, the game will fail" << endl;
            cout << "First, you need to select the difficulty of the map, there are three options ABC to choose from, if you enter other illegal characters, you will be prompted and re-enter" << endl;
            cout << "The initial position is Lobby, enter the selected direction according to the prompt" << endl;
            cout << "The input must start with go, otherwise a prompt will appear and you need to re-enter" << endl;
            cout << "If the direction is not within the selected range, you will be prompted and need to re-enter" << endl;
            cout << "When you find the princess, there will be a text prompt" << endl << "Encounter a monster, the game is over" << endl;
        }
    }
    string str;
    getline(cin, str);
    cout << "Please select a map mode: " << endl;
    cout << "A.Easy\t" <<  "B.Moderate\t" << "C.Difficult" << endl;
    cin >> opt;

    // Game difficulty selection: Easy Moderate Difficult 
    do{
        flag = 0;
        if( opt == 'A' ){
            side = 3;
            height = 3;
        }else if( opt == 'B' ){
            side = 5;
            height = 5;
        }else if( opt == 'C' ){
            side = 7;
            height = 7;
        }else{
            cout << "Illegal input, please re-enter: " << endl;
            flag = 1;
            cin >> opt;
        }
    }while(flag);

    getline(cin, str);

    // Create a map according to the selected difficulty
    map = new Map(side, height);

    // The current location is the lobby
    curLoc = map->Lobby;
}

// Calculate the number of room exits
int Adventure::ExitsNum()
{
    Rooms room = map->rooms[map->RoomNum(curLoc)];
    int count = 0;
    for( int i=0 ; i<6 ; i++ )
        if( room.link[i] == true )
            count++;
    return count;
}

// Export each export direction
void Adventure::CoutExits()
{
    bool flag = false;
    Rooms room = map->rooms[map->RoomNum(curLoc)];
    for( int i=0 ; i<6 ; i++ ){
        if( room.link[i] == true ){
            if( flag )
                cout << ", " << Dire[i];
            else    
                cout << " " << Dire[i];
            flag = true;
        }
    }
    cout << endl;
}

// Main game loop
void Adventure::Loop()
{
    bool FindPrincess = false;
    bool Victory = false;
    string str;
    bool bug;
    int dir;
    while(1){
        // cout << "curloc" << curLoc.x << " " << curLoc.y << " " << curLoc.z << endl;
        if( curLoc == map->Lobby )
            cout << "Welcome to the lobby. "<<endl;
        else{
            int type = (curLoc.x + curLoc.y + curLoc.z) % 6;
            cout << "You are in the " << RoomType[type] << " now" << endl;
        }
        cout << "There are " << ExitsNum() << " exits as:";
        CoutExits();
        cout << "Enter your command:" << endl;
        
        // Ensure that the input is correct
        do{
            bug = false;
            getline(cin, str);
            if( str.substr(0,2) == "go" ){
                dir = Direction(str.substr(3));
            }
            else
                bug = true;

            if( dir == -1 ){
                bug = true;
            }else{
                // Change the current position according to the input direction
                switch(dir){
                    case NORTH:
                        curLoc.x += 1;
                        break;
                    case SOUTH:
                        curLoc.x -= 1;
                        break;
                    case WEST:
                        curLoc.y -= 1;
                        break;
                    case EAST:
                        curLoc.y += 1;
                        break;
                    case UP:
                        curLoc.z += 1;
                        break;
                    case DOWN:
                        curLoc.z -= 1;
                        break;
                }
            }
            if( bug )
                cout << "Invalid input, please input again!" << endl;
        }while(bug);

        // Find the princess
        if( curLoc == map->Princess ){
            cout << "Congratulations on finding the princess, please take her away!" << endl;
            FindPrincess = true;
        }

        // Met a monster
        if( curLoc == map->Monster ){
            cout << "You met a monster!!" << endl;
            break;
        }

        // Take the princess to the lobby and win the game
        if( curLoc == map->Lobby && FindPrincess ){
            Victory = true;
            break;
        }
    }
    if( Victory )
        cout << "Congratulations, lucky to win!" << endl;
    else    
        cout << "Haha, you lose!" << endl;
}

// The selected direction is obtained by user input
int Adventure::Direction(const string& s)
{
    for( int i=0 ; i<6 ; i++ ){
    Rooms room = map->rooms[map->RoomNum(curLoc)];
        if( s == Dire[i] && room.link[i] == true )
            return i;
    }
    return -1;
}

// Start the game
void Adventure::Start()
{
    if( curLoc != map->Lobby )
        curLoc = map->Lobby;
    Loop();
}