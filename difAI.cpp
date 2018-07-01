//不同游戏类的不同AI实现文件
#include "difGame.h"
#include "difAI.h"
// 五子棋的AI加入几条简单的策略，具体的策略本身价值不是特别大因此就不再详细介绍
int FIRAI::value(int x, int y){
    static bool oneByOne=false;
    int sum=0;
    int Me = (game->getFirstPlayer()+oneByOne)%2;// self
    int thesize = game->getsize();
    for(int i = 1; i <= thesize; i ++){
        if(game->getMatrix(i, y)==Me){
            ++sum;
            if(i>1&&game->getMatrix(i-1, y)==Me){
                sum+=2;
                if(i>2&&game->getMatrix(i-2, y)==Me){
                    sum+=3;
                }
            }
         }
        if(game->getMatrix(x, i)==Me){
            ++sum;
            if(i>1&&game->getMatrix(x, i-1)==Me){
                sum+=2;
                if(i>2&&game->getMatrix(x,i-2)==Me){
                    sum+=3;
                }
            }
         }
        if(x+i<=thesize && y+i<=thesize&&game->getMatrix(x+i, y+i)==Me){
            ++sum;
            if(i>1&&game->getMatrix(x+i-1, y+i-1)==Me){
                sum+=2;
                if(i>2&&game->getMatrix(x+i-2, y+i-2)==Me){
                    sum+=3;
                }
            }
         }
        if(x-i>0&&y-i>0&&game->getMatrix(x-i, y-i)==Me){
            ++sum;
            if(i>1&&game->getMatrix(x-i+1, y-i+1)==Me){
                sum+=2;
                if(i>2&&game->getMatrix(x-i+2, y-i+2)==Me){
                    sum+=3;
                }
            }
         }
    }
    sum = sum*10+sin(x*3.14/thesize)*5+sin(y*3.14/thesize)*5;
    //oneByOne = !oneByOne;
    return sum;
}
//黑白棋的AI相对比较强力，有对地理位置的评估，在此基础上使用贪心法
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
        else if(!((x==2&&y ==2)||(x==game->getsize()-1&&y ==2)||(x==2&&y ==game->getsize()-1)||(x==game->getsize()-1&&y ==game->getsize()-1)))
            Total+=10;
        return Total;
}
    else
        return -100;
}
//围棋AI不进行单独实现，使用倒叙落子