//AI基类头文件
#pragma once

#include <iostream>
#include "goGameBase.h"
#include <ctime>
#include <cstdlib>

#include <QTime>

class goGameAIBase{
private:
    int size;
    bool Me = false;
protected:
    goGameBase* game;
public:
    goGameAIBase(goGameBase* _game):game(_game), size(_game->getsize()){
    }
    inline int getsize(){return size;}
    inline bool getMe(){return Me;}
    virtual int value(int,int){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int n = qrand()*100%997;
             return n;} // 单个的估值函数为虚函数，默认使用随机估值}
    int valueAll();
    ~goGameAIBase(){}
};
