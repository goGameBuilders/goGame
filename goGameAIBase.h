//AI基类头文件
#include <iostream>
#include "goGameBase.h"
#include <ctime>
#include <cstdlib>
class goGameAIBase{
private:
    int size;
protected:
    goGameBase* game;
public:
    goGameAIBase(goGameBase* _game):game(_game), size(_game->getsize()){
    }
    inline int getsize(){return size;}
    virtual int value(int, int){
        srand((unsigned)time(nullptr));
        return rand();} // 单个的估值函数为虚函数，默认使用随机估值
    int valueAll(){
        int place = 0;
        int Max = 0;
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
            {
                if(game->getwhich(i,j)==-1&&Max <= value(i, j))
                {
                    Max = value(i, j);
                    place = 100*i + j;
                }
            }
        return place; //由于返回值的问题，返回值为100*横坐标+纵坐标，解密需注意
    }

    ~goGameAIBase(){}
}
