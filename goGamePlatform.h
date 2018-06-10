#pragma once

#include "goGameBase.h"
#include "goGameUI.h"
#include "goGameNet.h"

#include <string>

using namespace std;

class goGamePlatform{

private:
    string type;      //游玩游戏的种类
    goGameBase *game; //游戏基类指针
    goGameUI *ui;   //UI类指针
    goGameNet *net; //通信类指针
public:
    goGamePlatform();
    void gameSelect(string myType); //决定生成游戏的指针
    ~goGamePlatform();

};
