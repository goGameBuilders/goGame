//不同游戏类的AI头文件
#pragma once

#include "goGameAIBase.h"
#include "goGameBase.h"
#include "difGame.h"
class FIRAI: public goGameAIBase{
public:
    FIRAI(goGameBase* _game):goGameAIBase(_game){}
    virtual int value(int, int);
};
