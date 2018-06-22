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

int ReversiAI::value(int x, int y){
    int Total = 0, sum = 0;
    int Me = game->getFirstPlayer();
    if(game->judge(x, y))
    {
        for(int i = x+1; i <=game->getsize(); i++)
        {
            if(game->getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(game->getMatrix(i, y)==Me&&sum == i-x-1&&sum > 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = x-1; i>0; i--)
        {
            if(game->getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(game->getMatrix(i, y)==Me&&sum == x-i-1&&sum > 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = y+1; i <=game->getsize(); i++)
        {
            if(game->getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(game->getMatrix(x, i)==Me&&sum == i-y-1&&sum > 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = y-1; i>0; i--)
        {
            if(game->getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(game->getMatrix(x, i)==Me&&sum == y-i-1&&sum > 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x+i)<=game->getsize()&&(y+i)<=game->getsize();i++)
        {
            if(game->getMatrix(x + i, y + i)== (Me+1)%2)
                ++sum;
            else if(game->getMatrix(x + i, y + i)== Me && sum == i-1 && sum> 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x-i)>0&&(y-i)>0;i++)
        {
            if(game->getMatrix(x - i, y - i)== (Me+1)%2)
                ++sum;
            else if(game->getMatrix(x - i, y - i)== Me && sum == i-1 && sum> 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x+i)<=game->getsize()&&(y-i)>0;i++)
        {
            if(game->getMatrix(x + i, y - i)== (Me+1)%2)
                ++sum;
            else if(game->getMatrix(x + i, y - i)== Me && sum == i-1 && sum> 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x-i) > 0 && (y+i)<=game->getsize();i++)
        {
            if(game->getMatrix(x - i, y + i)== (Me+1)%2)
                ++sum;
            else if(game->getMatrix(x - i, y + i)== Me && sum == i-1 && sum> 0)
            {
                Total+=sum;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
        if((x==1&&y ==1)||(x==game->getsize()&&y ==1)||(x==1&&y ==game->getsize())||(x==game->getsize()&&y ==game->getsize()))
        {
            Total+=100;
        }
        else if(x==1 ||x == game->getsize()|| y ==1 ||y ==game->getsize())
        {
            Total+=20;
        }
        else if((x==2&&y ==2)||(x==game->getsize()-1&&y ==2)||(x==2&&y ==game->getsize()-1)||(x==game->getsize()-1&&y ==game->getsize()-1))
            Total-=10;
        return Total;
}
    else
        return -100;
}
