//不同游戏类的AI头文件
#pragma once

#include "goGameAIBase.h"
#include "goGameBase.h"
#include "difGame.h"
#include "cmath"
// 所有的AI只需重载value（int， int）即可，虽然效率不是很高，但是接口统一，且不影响性能
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
class GoAI:public goGameAIBase{
public:
    GoAI(goGameBase* _game):goGameAIBase(_game){}
};
