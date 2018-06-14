#pragma once

#include "goGameBase.h"
#include "goGameAIBase.h"
#include "difGame.h"
#include "difAI.h"
#include "goGameNet.h"
#include <string>

using namespace std;

class goGamePlatform{

private:
    int type;      //游玩游戏的种类 1 五子棋  2 黑白棋 3 围棋
    int vsWho;      // 1 人机 2 人人  3 联网对战
    goGameBase *game = nullptr; //游戏基类指针
    goGameAIBase *gameAI = nullptr; //游戏AI类指针
    goGameNet *net; //通信类指针
public:
    goGamePlatform(){}
    void gameSelect(int myType, int myVsWho); //决定生成游戏的指针
    void restartGame();
    goGameBase* getgame(){return game;} //获得游戏指针
    goGameAIBase* getgameAI(){return gameAI;}//获得游戏AI的指针
    bool isPVE(){return vsWho-2;}//若vsAI则返回true
    ~goGamePlatform(){}
};
