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
    bool BorW; //AI代表的哪一方，0代表黑色，1代表白色
protected:
    goGameBase* game;
public:
    goGameAIBase(goGameBase* _game):game(_game), BorW(_game->getFirstPlayer()),size(_game->getsize()){
    }
    inline int getsize(){return size;}
    virtual int value(int,int){
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int n = qrand()*100%997;    //产生5以内的随机数
             return n;} // 单个的估值函数为虚函数，默认使用随机估值}
    int valueAll();
    ~goGameAIBase(){}
};
