#pragma once

#include "goGameBase.h"
#include "goGameAIBase.h"
#include "difGame.h"
#include "difAI.h"
#include <string>

using namespace std;

class goGamePlatform{

private:
    int type;      //游玩游戏的种类 1 五子棋  2 黑白棋 3 围棋
    int vsWho;      // 1 人机 2 人人  3 联网对战(主机)    4 联网对战(子机)
    goGameBase *game = nullptr; //游戏基类指针
    goGameAIBase *gameAI = nullptr; //游戏AI类指针
public:
    goGamePlatform(){}
    void gameSelect(int myType, int myVsWho); //决定生成游戏的指针
    void restartGame();
    goGameBase* getgame(){return game;} //获得游戏指针
    goGameAIBase* getgameAI(){return gameAI;}//获得游戏AI的指针
    bool isPVE()
    {
        if(vsWho <= 2)
            return vsWho-2;
        else
            return false;
    }//若vsAI则返回true
    int getType(){return type;}//获取游戏种类
    int getNet(){return vsWho;}//获取联机类型
    ~goGamePlatform(){}
};
