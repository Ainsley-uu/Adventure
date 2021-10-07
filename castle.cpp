#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include "castle.h"
using namespace std;

Castle::Castle()
{
    getPrincess = false;
    int i, j;
    cout << "Your mission is going to the castle to save the princess. " << endl;
    cout << "The castle has 25 rooms and the structure of it is as follow:" << endl;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
            cout << i * 5 + j << "\t";
        cout << endl;
    }
    cout << "Now, you are in the room 22 called lobby." << endl;
    cout << "Be careful to the monster! Good luck to you." << endl;
    cout << "-------------------------------------------------" << endl;
}

Castle::~Castle()
{
    while (!castle.empty())
    {
        vector<Room *>::iterator item = castle.end();
        castle.pop_back();
        delete (*item);
    }
}
/*初始化城堡中的房间信息，类似于5×5的矩阵方格*/
void Castle::Init_Map()
{
    int i, j, k;
    srand(time(NULL)); //随机数种子
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
        {
            Room *room = new Room;
            string name;
            name = "room " + to_string(i * 5 + j); //对房间的名字命名
            room->roomname = name;
            room->EastExit = room->WestExit = room->UpExit = room->DownExit = false;
            room->Monster = room->Princess = room->Random_door = room->Map = false;
            room->ExitNum = 0;
            if (i == 4 && j == 2) //进入城堡的起点，房间名为“lobby”，为第22号房间（以0为起点计算）
            {
                room->EastExit = room->WestExit = room->UpExit = true;
                room->ExitNum = 3;
            }
            else if (i == 0) //处理0~4号的房间
            {
                room->DownExit = true; //确保有向下的出口
                room->ExitNum++;
                if (rand() % 3 != 0) // 有2/3的概率生成出口
                {
                    room->EastExit = true;
                    room->ExitNum++;
                }
                if (rand() % 3 != 0)
                {
                    room->WestExit = true;
                    room->ExitNum++;
                }
                if (j == 0 || j == 4)
                {
                    if (j == 0 && room->WestExit) //处理0号房间出现有西出口的情况
                    {
                        room->WestExit = false;
                        --room->ExitNum;
                    }
                    if (j == 4 && room->EastExit) //处理4号房间出现有东出口的情况
                    {
                        room->EastExit = false;
                        --room->ExitNum;
                    }
                }
            }
            else if (i == 4) //处理20~24号的房间
            {
                room->UpExit = true; //确保有向上的出口
                room->ExitNum++;
                if (rand() % 3 != 0) //有2/3的概率生成东出口
                {
                    room->EastExit = true;
                    room->ExitNum++;
                }
                if (rand() % 3 != 0) //有2/3的概率生成西出口
                {
                    room->WestExit = true;
                    room->ExitNum++;
                }
                if (j == 0 || j == 4)
                {
                    if (j == 0 && room->WestExit) //处理房间20出现有西门的情况
                    {
                        room->WestExit = false;
                        --room->ExitNum;
                    }
                    if (j == 4 && room->EastExit) //处理房间24出现有东门的情况
                    {
                        room->EastExit = false;
                        --room->ExitNum;
                    }
                }
            }
            else if (j == 0) //处理房间5，10,15
            {
                room->EastExit = true; //确保房间有东出口
                room->ExitNum++;
                if (rand() % 3 != 0)
                {
                    room->UpExit = true;
                    room->ExitNum++;
                }
                if (rand() % 3 != 0)
                {
                    room->DownExit = true;
                    room->ExitNum++;
                }
            }
            else if (j == 4) //处理房间9，14，19
            {
                room->WestExit = true; //确保房间有西出口
                room->ExitNum++;
                if (rand() % 3 != 0)
                {
                    room->UpExit = true;
                    room->ExitNum++;
                }

                if (rand() % 3 != 0)
                {
                    room->DownExit = true;
                    room->ExitNum++;
                }
            }
            else
            {
                /*其余房间默认有4个完整的出口*/
                room->DownExit = room->EastExit = room->UpExit = room->WestExit = true;
                room->ExitNum = 4;
            }
            castle.push_back(room);
        }
}

/*打印房间信息*/
void Castle::PrintInfo(Room *room)
{
    if (!room->Map)
        cout << "Welcome to the " << room->roomname << ". ";
    else
    {
        cout << "Welcome to the " << room->roomname << ". ";
        cout << "You get a map of the castle. It can tell you the secret of the castle! " << endl;
        cout << "The princess is locked in the Room " << meg["Princess"] << ". " << endl;
        cout << "The monster guards in the Room " << meg["Monster"] << ". " << endl;
    }

    if (room->ExitNum != 1)
        cout << "There are " << room->ExitNum << " exits: ";
    else
        cout << "There is " << room->ExitNum << " exit: ";

    string name[4];
    int i = 0;
    if (room->EastExit)
        name[i++] = "east";
    if (room->WestExit)
        name[i++] = "west";
    if (room->UpExit)
        name[i++] = "up";
    if (room->DownExit)
        name[i++] = "down";
    for (i = 0; i < room->ExitNum; i++)
    {
        cout << name[i];
        if (i == room->ExitNum - 2)
            cout << " and ";
        else if (i == room->ExitNum - 1)
            cout << "." << endl;
        else
            cout << ", ";
    }
    cout << "Enter your command: ";
}

void Castle::Run()
{
    Room *cur = castle[22];
    int pos = 22;
    string go, dir;
    while (1)
    {
        if (!cur->Random_door)
            PrintInfo(cur);
        cin >> go >> dir;
        if (dir == "east")
        {
            if (!cur->EastExit)
            {
                cout << "The exit doesn't exist!" << endl;
                continue;
            }
            else
            {
                cur = castle[++pos]; //向东走则当前位置pos+1
            }
        }
        else if (dir == "west")
        {
            if (!cur->WestExit)
            {
                cout << "The exit doesn't exist!" << endl;
                continue;
            }
            else
            {
                cur = castle[--pos]; //向西走则当前位置pos-1
            }
        }
        else if (dir == "up")
        {
            if (!cur->UpExit)
            {
                cout << "The exit doesn't exist!" << endl;
                continue;
            }
            else
            {
                pos -= 5;
                cur = castle[pos]; //向上走则当前位置pos-5
            }
        }
        else if (dir == "down")
        {
            if (!cur->DownExit)
            {
                cout << "The exit doesn't exist!" << endl;
                continue;
            }
            else
            {
                pos += 5;
                cur = castle[pos]; //向上走则当前位置pos+5
            }
        }
        else //输入的方向非法
        {
            cout << "The exit is illegal! " << endl;
        }
        /*Judge------------------------------------------------------------------*/
        while (cur->Random_door) //进入了带有任意门的房间
        {
            int roomnum;
            cout << "-------------------------------------------------" << endl;
            cout << "Welcome to the Random_door! "
                 << "You can go to any room! " << endl;
            cout << "Please enter the room you want to go(0~24): ";
            cin >> roomnum;
            if (roomnum == pos)
                continue;
            pos = roomnum;
            cur = castle[pos];
        }

        if (cur->Monster) //进入了有怪物的房间
        {
            cout << "--------------------------------------------------------" << endl;
            cout << "You are eaten by the monster! Game over!" << endl;
            return; //游戏失败并结束
        }

        if (cur->Princess) //进入了有公主的房间
        {
            if (!getPrincess)
            {
                getPrincess = true; //成功获取公主
                cout << "------------------------------------------------------" << endl;
                cout << "You get the princess, run out of the castle quickly!" << endl;
            }
        }

        if (getPrincess && pos == 22) //成功获取公主并且回到起点“lobby”
        {
            cout << "------------------------------------------------" << endl;
            cout << "Successfully save the princess! "
                 << "You win!" << endl;
            return; //游戏胜利并结束
        }

        if (!cur->Princess)
            cout << "---------------------------------------------------------" << endl;
    }
}

void Castle::RandomSet()
{
    srand(time(NULL));
    int princess = rand() % 25;                                    //随机产生带有公主的房间
    int monster = rand() % 25;                                     //随机产生带有怪物的房间
    int random_door = rand() % 25;                                 //随机产生带有任意门的房间
    while (princess == monster || princess == 22 || monster == 22) //确保公主与怪物不在同一房间，且都不位于起点“lobby”
    {
        princess = rand() % 25;
        monster = rand() % 25;
    }
    castle[princess]->Princess = true;
    meg["Princess"] = princess;
    castle[monster]->Monster = true;
    meg["Monster"] = monster;
    //确保任意门与公主，怪物不在同一房间，且不位于起点“lobby”
    while (random_door == princess || random_door == monster || random_door == 22)
    {
        random_door = rand() % 25;
    }
    castle[random_door]->Random_door = true;
    int map = rand() % 25; //随机产生带有地图的房间
    //确保带有地图的房间与公主，怪物，任意门不在同一房间，且不位于起点“lobby”
    while (map == random_door || map == monster || map == princess || map == 22)
    {
        map = rand() % 25;
    }
    castle[map]->Map = true;
    /*对于特殊类别的房间重新命名，覆盖由原先初始化序号命名房间的名字*/
    castle[princess]->roomname = "Princess Room";
    castle[monster]->roomname = "Monster Room";
    castle[random_door]->roomname = "Random_Door";
    castle[map]->roomname = "Map_Room";
    castle[22]->roomname = "lobby";
}