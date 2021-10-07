#ifndef _CASTLE_H_
#define _CASTLE_H_

#include <string>
#include <vector>
#include<map>
using namespace std;

struct Room
{
    string roomname;
    int ExitNum;
    bool EastExit, WestExit, UpExit, DownExit; //定义出口是否存在
    bool Monster;     //定义房间是否有怪物
    bool Princess;    //定义房间是否有公主
    bool Random_door; //定义房间是否为任意门
    bool Map;         //定义房间是否有地图
};

class Castle
{
private:
    vector<Room *> castle;
    bool getPrincess;  //是否成功解救公主
    map<string, int> meg;

public:
    Castle();
    ~Castle();
    void Init_Map();   //初始化城堡
    void RandomSet();  //随机设置房间的类别：有公主，有怪物
    void Run();        
    void PrintInfo(Room* room);
};


#endif