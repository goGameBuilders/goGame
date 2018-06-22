#include "goGameBase.h"
#include "difGame.h"

// FIR函数实现
FIR::FIR() :goGameBase(){
}

FIR::FIR(int asize) :goGameBase(asize){
}

void FIR::updateMatrix(int step0) {
	touchMatrix(getPath(step0 - 1, 1), getPath(step0 - 1, 0), (getFirstPlayer() + step0) % 2);
}
int FIR::isEnd() {
    if(getstep() == getsize()*getsize())
        return 2;
    // 平局
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 1 && getwhich(i, j + 1) == 1 && getwhich(i, j + 2) == 1 && getwhich(i, j + 3) == 1 && getwhich(i, j + 4) == 1)
				return 1;
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(j, i) == 1 && getwhich(j + 1, i) == 1 && getwhich(j + 2, i) == 1 && getwhich(j + 3, i) == 1 && getwhich(j + 4, i) == 1)
				return 1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 1 && getwhich(i + 1, j + 1) == 1 && getwhich(i + 2, j + 2) == 1 && getwhich(i + 3, j + 3) == 1 && getwhich(i + 4, j + 4) == 1)
				return 1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i+4, j) == 1 && getwhich(i + 3, j + 1) == 1 && getwhich(i + 2, j + 2) == 1 && getwhich(i + 1, j + 3) == 1 && getwhich(i, j + 4) == 1)
				return 1;
	//白棋胜利
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 0 && getwhich(i, j + 1) == 0 && getwhich(i, j + 2) == 0 && getwhich(i, j + 3) == 0 && getwhich(i, j + 4) == 0)
				return -1;
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(j, i) == 0 && getwhich(j + 1, i) == 0 && getwhich(j + 2, i) == 0 && getwhich(j + 3, i) == 0 && getwhich(j + 4, i) == 0)
				return -1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 0 && getwhich(i + 1, j + 1) == 0 && getwhich(i + 2, j + 2) == 0 && getwhich(i + 3, j + 3) == 0 && getwhich(i + 4, j + 4) == 0)
				return -1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i + 4, j) == 0 && getwhich(i + 3, j + 1) == 0 && getwhich(i + 2, j + 2) == 0 && getwhich(i + 1, j + 3) == 0 && getwhich(i, j + 4) == 0)
				return -1;
	//黑棋胜利
	return 0;
}
// 黑白棋的函数实现
Reversi::Reversi():goGameBase(){
    touchMatrix(4,4,1);
    touchMatrix(5,5,1);
    touchMatrix(4,5,0);
    touchMatrix(5,4,0);
}
Reversi::Reversi(int size):goGameBase(size){
    touchMatrix(4,4,1);
    touchMatrix(5,5,1);
    touchMatrix(4,5,0);
    touchMatrix(5,4,0);
}
void Reversi::updateMatrix(int step0){
    bool Me = step0 % 2; //还需确定敌我双方问题
    for(int i = x+1; i <=getsize(); i++)
    {
        int sum=0;
        if(getMatrix(i, y)==(Me+1)%2)
            ++sum;
        else if(getMatrix(i, y)==Me&&sum == i-x-1&&sum > 0)
        {
            for(int j =x+1; j <i; j ++)
                touchMatrix(j, y, Me);
            break;
        }
        else
            break;
    }
    for(int i = x-1; i>0; i--)
    {
        int sum=0;
        if(getMatrix(i, y)==(Me+1)%2)
            ++sum;
        else if(getMatrix(i, y)==Me&&sum == x-i-1&&sum > 0)
        {
            for(int j =x-1; j >i; j --)
                touchMatrix(j, y, Me);
            break;
        }
        else
            break;
    }
    for(int i = y+1; i <=getsize(); i++)
    {
        int sum=0;
        if(getMatrix(x, i)==(Me+1)%2)
            ++sum;
        else if(getMatrix(x, i)==Me&&sum == i-y-1&&sum > 0)
        {
            for(int j =y+1; j <i; j ++)
                touchMatrix(x, j, Me);
            break;
        }
        else
            break;
    }
    for(int i = y-1; i>0; i--)
    {
        int sum=0;
        if(getMatrix(x, i)==(Me+1)%2)
            ++sum;
        else if(getMatrix(x, i)==Me&&sum == y-i-1&&sum > 0)
        {
            for(int j =y-1; j >i; j --)
                touchMatrix(x, j, Me);
            break;
        }
        else
            break;
    }
    for(int i = 1;(x+i)<=getsize()&&(y+i)<=getsize();i++)
    {
        int sum = 0;
        if(getMatrix(x + i, y + i)== (Me+1)%2)
            ++sum;
        else if(getMatrix(x + i, y + i)== Me && sum == i-1 && sum> 0)
        {
            for(int j = 1; j < i; j ++)
                touchMatrix(x+j, y+j, Me);
            break;
        }
        else
            break;
    }
    for(int i = 1;(x-i)>0&&(y-i)>0;i++)
    {
        int sum = 0;
        if(getMatrix(x - i, y - i)== (Me+1)%2)
            ++sum;
        else if(getMatrix(x - i, y - i)== Me && sum == i-1 && sum> 0)
        {
            for(int j = 1; j < i; j ++)
                touchMatrix(x-j, y-j, Me);
            break;
        }
        else
            break;
    }
    for(int i = 1;(x+i)<=getsize()&&(y-i)>0;i++)
    {
        int sum = 0;
        if(getMatrix(x + i, y - i)== (Me+1)%2)
            ++sum;
        else if(getMatrix(x + i, y - i)== Me && sum == i-1 && sum> 0)
        {
            for(int j = 1; j < i; j ++)
                touchMatrix(x+j, y-j, Me);
            break;
        }
        else
            break;
    }
    for(int i = 1;(x-i) > 0 && (y+i)<=getsize();i++)
    {
        int sum = 0;
        if(getMatrix(x - i, y + i)== (Me+1)%2)
            ++sum;
        else if(getMatrix(x - i, y + i)== Me && sum == i-1 && sum> 0)
        {
            for(int j = 1; j < i; j ++)
                touchMatrix(x-j, y+j, Me);
            break;
        }
        else
            break;
    }
}
bool Reversi::judge(int x, int y){
    bool Me = getWhoTurn();
    if (x > 0 && x <= size && y > 0 && y <= size && Matrix[x][y] == -1)
    {
        for(int i = x+1; i <=getsize(); i++)
        {
            int sum=0;
            if(getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(getMatrix(i, y)==Me&&sum == i-x-1&&sum > 0)
                return true;
            else
                break;
        }
        for(int i = x-1; i>0; i--)
        {
            int sum=0;
            if(getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(getMatrix(i, y)==Me&&sum == x-i-1&&sum > 0)
                return true;
            else
                break;
        }
        for(int i = y+1; i <=getsize(); i++)
        {
            int sum=0;
            if(getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(getMatrix(x, i)==Me&&sum == i-y-1&&sum > 0)
                return true;
            else
                break;
        }
        for(int i = y-1; i>0; i--)
        {
            int sum=0;
            if(getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(getMatrix(x, i)==Me&&sum == y-i-1&&sum > 0)
                return true;
            else
                break;
        }
        for(int i = 1;(x+i)<=getsize()&&(y+i)<=getsize();i++)
        {
            int sum = 0;
            if(getMatrix(x + i, y + i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x + i, y + i)== Me && sum == i-1 && sum> 0)
                return true;
            else
                break;
        }
        for(int i = 1;(x-i)>0&&(y-i)>0;i++)
        {
            int sum = 0;
            if(getMatrix(x - i, y - i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x - i, y - i)== Me && sum == i-1 && sum> 0)
                return true;
            else
                break;
        }
        for(int i = 1;(x+i)<=getsize()&&(y-i)>0;i++)
        {
            int sum = 0;
            if(getMatrix(x + i, y - i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x + i, y - i)== Me && sum == i-1 && sum> 0)
                return true;
            else
                break;
        }
        for(int i = 1;(x-i) > 0 && (y+i)<=getsize();i++)
        {
            int sum = 0;
            if(getMatrix(x - i, y + i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x - i, y + i)== Me && sum == i-1 && sum> 0)
                return true;
            else
                break;
        }
    }
}
int isEnd(){

}
//其他自定义棋类游戏的实现
