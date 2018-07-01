//不同游戏类的AI头文件
#pragma once

#include "goGameAIBase.h"
#include "goGameBase.h"
#include "difGame.h"
#include "cmath"
class FIRAI: public goGameAIBase{
public:
    FIRAI(goGameBase* _game):goGameAIBase(_game){}
    virtual int value(int, int);
};

class ReversiAI:public goGameAIBase{
public:
    ReversiAI(goGameBase* _game):goGameAIBase(_game){}
    virtual int value(int , int);
};
