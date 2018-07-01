//AI基类实现文件
#include "goGameBase.h"
#include "goGameAIBase.h"

int goGameAIBase::valueAll(){
        int place = 0;
        int Max = 0;
        for(int i = 1; i <= size; ++i)
            for(int j = 1; j <= size; ++j)
            {
                int temp = value(i, j);
                if(game->judge(i,j) &&Max <= temp)
                {
                    Max = temp;
                    place = 100*i + j;
                }
            }
        return place; //由于返回值的问题，返回值为100*横坐标+纵坐标，解密需注意
    }
