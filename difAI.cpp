//不同游戏类的不同AI实现文件
#include "difGame.h"
#include "difAI.h"

int FIRAI::value(int x, int y){
    int sum=0;
    int theOpposite = (1+game->getFirstPlayer())%2;
    int thesize = game->getsize();
    for(int i = 1; i <= thesize; i ++){
        if(game->getMatrix(i, y)==theOpposite)
            ++sum;
        if(game->getMatrix(x, i)==theOpposite)
            ++sum;
        if(x+i<=thesize && y+i<=thesize&&game->getMatrix(x+i, y+i)==theOpposite)
            ++sum;
        if(x-i>0&&y-i>0&&game->getMatrix(x-i, y-i)==theOpposite)
            ++sum;
    }
    return sum;
}
